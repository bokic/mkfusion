#include "qtextparser.h"

#include <QDomDocument>
#include <QStringList>
#include <QTextStream>
#include <QFileInfo>
#include <QRegExp>
#include <QFile>
#include <QDir>

QList<QTextParserLanguageDefinition> languageDefinitions;

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
                            QString tokenToken = token_node.attributes().namedItem("Token").nodeValue();
                            QString tokenIgnoreTerminate = token_node.attributes().namedItem("IgnoreTerminate").nodeValue();

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
                            token.tokenString = tokenToken;
                            token.ignoreTerminateString = tokenIgnoreTerminate.compare("true", Qt::CaseInsensitive);
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
        QStringList fileLines;

        ts.setDevice(&file);
        ts.setCodec("UTF-8");
        ts.setAutoDetectUnicode(true);

        while(!ts.atEnd())
        {
            fileLines.append(ts.readLine());
        }

        file.close();

        QString fileExtension = finfo.suffix();

        setTextTypeByFileExtension(fileExtension);

        parseTextLines(fileLines);
    }
}

void QTextParser::parseText(const QString &text, const QString &fileExt)
{
    setTextTypeByFileExtension(fileExt);

    parseTextLines(text.split(QRegExp("(\r\n|\n\r|\r|\n)")));
}

void QTextParser::parseTextLines(const QStringList &lines)
{
    int cur_lines = 0;
    int cur_column = 0;

    while(parseElement(lines, cur_lines, cur_column, language.startsWith));
}

int QTextParser::findElement(const QStringList &lines, int &cur_lines, int &cur_column, const QStringList &tokens, QString &token)
{
    int choosen_position = -1;
    QString choosen_token;

    while ((choosen_position == -1)&&(cur_lines < lines.count()))
    {
        if (cur_column >= lines.at(cur_lines).length())
        {
            cur_column = 0;
            cur_lines++;
            continue;
        }

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


                QRegExp reg(searchRegEx);

                int index = reg.indexIn(lines.at(cur_lines), cur_column);

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
                }
            }
            else
            {
                qDebug("Parser error. Unknown token. File: %s, line: %u", __FILE__, __LINE__);
            }
        }
    }

    token = choosen_token;

    return choosen_position;
}

bool QTextParser::parseElement(const QStringList &lines, int &cur_lines, int &cur_column, const QStringList &tokens)
{
    int closes_position;
    QString choosen_token;

    closes_position = findElement(lines, cur_lines, cur_column, tokens, choosen_token);

    // Parses closes token found
    if (closes_position >= 0)
    {
        if (language.tokens[choosen_token].tokenString.isEmpty())
        {
            // start end token
            QRegExp reg(language.tokens[choosen_token].startString);
            int index = reg.indexIn(lines.at(cur_lines), cur_column);

            if(index >= 0)
            {
                cur_column += reg.cap(0).length();

                QStringList newTokens = language.tokens[choosen_token].nestedTokens;

                QString endToken = choosen_token + "_end";

                newTokens.prepend(endToken);

                choosen_token.clear();

                while(choosen_token != endToken)
                {
                    closes_position = findElement(lines, cur_lines, cur_column, newTokens, choosen_token);
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
            QRegExp reg(language.tokens[choosen_token].tokenString);
            int index = reg.indexIn(lines.at(cur_lines), cur_column);

            if(index >= 0)
            {
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
