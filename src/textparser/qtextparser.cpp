#include "qtextparser.h"

#include <QDomDocument>
#include <QStringList>
#include <QTextStream>
#include <QFileInfo>
#include <QRegExp>
#include <QDebug>
#include <QFile>
#include <QDir>

QList<QTextParser::QTextParserLanguageDefinition> languageDefinitions;

QTextParser::QTextParser():
    language()
{
}

void QTextParser::loadParserDefinitionsFromDir(const QString &dir)
{
    QDir l_dir;

    l_dir.setPath(dir);

    QStringList l_files = l_dir.entryList(QStringList() << "*.xml");

    languageDefinitions.clear();

    foreach(QString l_file, l_files)
    {
        QDomDocument doc(l_file);

        QFile file(l_file);

        if (!file.open(QIODevice::ReadOnly))
        {
            continue;
        }

        if (!doc.setContent(&file))
        {
            file.close();

            continue;
        }

        file.close();

        if (doc.childNodes().count() == 1)
        {
            QDomNode language_node = doc.childNodes().at(0);

            if (language_node.nodeName() == "language")
            {
                QTextParserLanguageDefinition def;

                QString languageName = language_node.attributes().namedItem("Name").nodeValue();
                QString caseSensitivity = language_node.attributes().namedItem("CaseSensitivity").nodeValue();
                QString defaultExtensions = language_node.attributes().namedItem("DefaultFileExtensions").nodeValue();
                QString startsWith = language_node.attributes().namedItem("StartsWith").nodeValue();

                def.languageName = languageName;
                def.caseSensitivity = caseSensitivity.compare("true", Qt::CaseInsensitive);
                def.defaultExtensions = defaultExtensions.split(',');
                def.startsWith = startsWith.split(',');

                // Iterate thry tokens
                if (language_node.childNodes().count() == 1)
                {
                    QDomNode tokens_node = language_node.childNodes().at(0);

                    if (tokens_node.nodeName() == "tokens")
                    {
                        for(int tokenIndex = 0; tokenIndex < tokens_node.childNodes().count(); tokenIndex++)
                        {
                            QDomNode token_node = tokens_node.childNodes().at(tokenIndex);
                            QTextParserLanguageDefinitionToken token;

                            if (token_node.nodeName() != "token")
                            {
                                continue;
                            }

                            QString tokenName = token_node.attributes().namedItem("Name").nodeValue();
                            QString tokenStartString = token_node.attributes().namedItem("StartString").nodeValue();
                            QString tokenEndString = token_node.attributes().namedItem("EndString").nodeValue();
                            QString tokenTokenString = token_node.attributes().namedItem("TokenString").nodeValue();
                            QString tokenIgnoreTerminate = token_node.attributes().namedItem("IgnoreTerminate").nodeValue();
                            QString tokenTextColor = token_node.attributes().namedItem("TextColor").nodeValue();

                            QDomNode nestedTokens_node = token_node.namedItem("nested_tokens");
                            QString tokenNestedTokens;
                            QString tokenNestedTokensRequireAll;
                            QString tokenNestedTokensInSameOrder;

                            if (nestedTokens_node.isElement())
                            {
                                tokenNestedTokens = nestedTokens_node.attributes().namedItem("names").nodeValue();
                                tokenNestedTokensRequireAll = nestedTokens_node.attributes().namedItem("require_all").nodeValue();
                                tokenNestedTokensInSameOrder = nestedTokens_node.attributes().namedItem("require_in_same_order").nodeValue();
                            }

                            token.name = tokenName;
                            token.startString = tokenStartString;
                            token.endString = tokenEndString;
                            token.tokenString = tokenTokenString;
                            token.ignoreTerminateString = tokenIgnoreTerminate.compare("true", Qt::CaseInsensitive);
                            token.textColor = tokenTextColor;
                            if (tokenNestedTokens.isEmpty())
                            {
                                token.nestedTokens = QStringList();
                            }
                            else
                            {
                                token.nestedTokens = tokenNestedTokens.split(',');
                            }
                            token.nestedTokensRequireAll = tokenNestedTokensRequireAll.compare("true", Qt::CaseInsensitive);
                            token.nestedTokensInSameOrder = tokenNestedTokensInSameOrder.compare("true", Qt::CaseInsensitive);

                            def.tokens[tokenName] = token;
                        }
                    }
                }

                languageDefinitions.append(def);
            }
        }
    }
}

void QTextParser::setTextTypeByFileExtension(const QString &fileExt)
{
    if (languageDefinitions.count() == 0)
    {
         QTextParser::loadParserDefinitionsFromDir(".");
    }

    bool found = false;

    for(int c = 0; c < languageDefinitions.count(); c++)
    {
        QStringList exts = languageDefinitions.at(c).defaultExtensions;

        if (exts.contains(fileExt))
        {
            language = languageDefinitions.at(c);
            found = true;
            break;
        }
    }

    if (!found)
    {
        language = QTextParserLanguageDefinition();
    }
}

void QTextParser::setTextTypeByLanguageName(const QString &langName)
{
    if (languageDefinitions.count() == 0)
    {
         QTextParser::loadParserDefinitionsFromDir(".");
    }

    bool found = false;

    for(int c = 0; c < languageDefinitions.count(); c++)
    {
        if (languageDefinitions.at(c).languageName.compare(langName, Qt::CaseInsensitive) == 0)
        {
            language = languageDefinitions.at(c);
            found = true;
            break;
        }
    }

    if (!found)
    {
        language = QTextParserLanguageDefinition();
    }
}

void QTextParser::parseFile(const QString &fileName)
{
    QFileInfo finfo(fileName);

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream ts;
        QTextParserLines fileLines;

        ts.setDevice(&file);
        ts.setCodec("UTF-8");
        ts.setAutoDetectUnicode(true);

        while(!ts.atEnd())
        {
            QTextParserLine line;
            line.Content = ts.readLine();
            line.EndLine = EndLineTypeCRLFEndLine;
            fileLines.append(line);
        }

        file.close();

        QString fileExtension = finfo.suffix();

        setTextTypeByFileExtension(fileExtension);

        parseTextLines(fileLines);
    }
}

void QTextParser::parseText(const QString &text, const QString &fileExt)
{
    QTextParserLines fileLines;

    setTextTypeByFileExtension(fileExt);

    foreach(QString curline, text.split(QRegExp("(\r\n|\n\r|\r|\n)")))
    {
        QTextParserLine line;
        line.Content = curline;
        line.EndLine = EndLineTypeCRLFEndLine;
        fileLines.append(line);
    }

    parseTextLines(fileLines);
}

void QTextParser::parseTextLines(QTextParserLines &lines)
{
    int cur_lines = 0;
    int cur_column = 0;

    while(parseElement(lines, cur_lines, cur_column, language.startsWith));
}

int QTextParser::findElement(const QTextParserLines &lines, int &cur_line, int &cur_column, const QStringList &tokens, QString &token)
{
    int choosen_position = -1;
    QString choosen_token;

    if ((tokens.count() == 0)||(cur_line >= lines.count()))
    {
        return choosen_position;
    }

    while (cur_line < lines.count())
    {
        if (cur_column >= lines.at(cur_line).Content.length())
        {
            cur_column = 0;
            cur_line++;
            continue;
        }

        QString line = lines.at(cur_line).Content;

        // Searches for closes token
        foreach(QString name, tokens)
        {
            bool ends_token = false;

            if (name.endsWith("_end"))
            {
                name = name.left(name.length() - 4);
                ends_token = true;
            }

            if(language.tokens.contains(name))
            {
                QString searchRegEx;
                if (!ends_token)
                {
                    searchRegEx = language.tokens[name].tokenString;
                    if (searchRegEx.isEmpty())
                    {
                        searchRegEx = language.tokens[name].startString;
                    }
                }
                else
                {
                    searchRegEx = language.tokens[name].endString;
                }


                QRegExp reg(searchRegEx, Qt::CaseInsensitive);

                int index = reg.indexIn(line, cur_column);

                if ((index >= 0)&&((choosen_position < 0)||(index < choosen_position)))
                {
                    choosen_position = index;

                    if (!ends_token)
                    {
                        choosen_token = name;
                    }
                    else
                    {
                        choosen_token = name + "_end";
                    }

                    token = choosen_token;

                    return choosen_position;
                }
            }
            else
            {
                qDebug("Parser error. Unknown token. File: %s, line: %u", __FILE__, __LINE__);
            }
        }

        if (choosen_position >= 0)
        {
            break;
        }

        cur_line++;
        cur_column = 0;
    }

    token = choosen_token;

    if (choosen_position >= 0)
    {
        cur_column = choosen_position;
    }

    return choosen_position;
}

bool QTextParser::parseElement(QTextParserLines &lines, int &cur_line, int &cur_column, const QStringList &tokens)
{
    int closes_position;
    QString choosen_token;

    closes_position = findElement(lines, cur_line, cur_column, tokens, choosen_token);

    // Parses closes token found
    if (closes_position >= 0)
    {
        if (language.tokens[choosen_token].tokenString.isEmpty())
        {
            // start end token
            QString targetToken;
            QString realToken;

            if (!choosen_token.endsWith("_end"))
            {
                realToken = choosen_token;
                targetToken = language.tokens[realToken].startString;
            }
            else
            {
                realToken = choosen_token.left(choosen_token.count() - 4);
                targetToken = language.tokens[realToken].endString;
            }


            QRegExp reg(targetToken, Qt::CaseInsensitive);
            int index = reg.indexIn(lines.at(cur_line).Content, cur_column);

            if(index >= 0)
            {
                if (!language.tokens[realToken].textColor.isEmpty())
                {
                    QColor col(language.tokens[realToken].textColor);

                    QTextParserColorItem colorItem;

                    colorItem.foregroundColor = col;

                    colorItem.index = index;

                    Q_ASSERT(reg.cap(0).length() > 0);
                    colorItem.length = reg.cap(0).length();

                    colorItem.type = realToken;

                    qDebug() << "Element: " << colorItem.type << "(" << reg.cap() << ")" << ":" << cur_line << ":" << index;

                    lines[cur_line].ColorItems.append(colorItem);
                }

                Q_ASSERT(reg.cap(0).length() > 0);
                cur_column += reg.cap(0).length();


                if (!choosen_token.endsWith("_end"))
                {
                    QStringList newTokens = language.tokens[choosen_token].nestedTokens;
                    QString endToken = choosen_token + "_end";
                    newTokens.prepend(endToken);
                    choosen_token.clear();

                    while(choosen_token != endToken)
                    {
                        // TODO: Not optimal element search. parseElement called after findElement call.
                        if (findElement(lines, cur_line, cur_column, newTokens, choosen_token) == -1)
                        {
                            break;
                        }

                        parseElement(lines, cur_line, cur_column, newTokens);
                    }
                }
            }
            else
            {
                qDebug("Parser error. File: %s, line: %u", __FILE__, __LINE__);
            }
        }
        else
        {
            // token
            QRegExp reg(language.tokens[choosen_token].tokenString, Qt::CaseInsensitive);
            int index = reg.indexIn(lines.at(cur_line).Content, cur_column);

            if(index >= 0)
            {
                if (!language.tokens[choosen_token].textColor.isEmpty())
                {
                    QColor col(language.tokens[choosen_token].textColor);

                    QTextParserColorItem colorItem;

                    colorItem.foregroundColor = col;

                    colorItem.index = index;
                    colorItem.length = reg.cap(0).length();

                    lines[cur_line].ColorItems.append(colorItem);
                }

                cur_column += reg.cap(0).length();
            }
            else
            {
                qDebug("Parser error. File: %s, line: %u", __FILE__, __LINE__);
            }
        }

        return true;
    }

    return false;
}
