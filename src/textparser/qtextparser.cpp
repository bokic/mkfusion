/****************************************************************************
**
** Author: Boris Barbulovski(bbarbulovski@gmail.com)
**
** This file is part of the MKFusion(http://mkfusion.bokicsoft.com/ or
** https://github.com/bokic/mkfusion/) project.
**
** $QT_BEGIN_LICENSE:LGPL$
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qtextparser.h"

#include <limits.h>

#include <QDomDocument>
#include <QStringList>
#include <QTextStream>
#include <QFileInfo>
#include <QRegExp>
#include <QDebug>
#include <QFile>
#include <QList>
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

    for(const QString &l_file: l_files)
    {
        QDomDocument doc(l_file);
        QVector<QString> tmpNestedTokens;

        QFile file((dir) + "/" + l_file);

        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "Could not open" << l_file << "file.";

            continue;
        }

        if (!doc.setContent(&file))
        {
            file.close();

            qDebug() << "Invalid XML file" << l_file;

            continue;
        }

        file.close();

        if (doc.childNodes().count() == 1)
        {
            QDomNode language_node = doc.childNodes().at(0);

            if (language_node.nodeName() == "language")
            {
                QTextParserLanguageDefinition def;

                const QString languageName = language_node.attributes().namedItem("Name").nodeValue();
                const QString caseSensitivity = language_node.attributes().namedItem("CaseSensitivity").nodeValue();
                const QString defaultExtensions = language_node.attributes().namedItem("DefaultFileExtensions").nodeValue();
                const QString startsWith = language_node.attributes().namedItem("StartsWith").nodeValue();

                def.languageName = languageName;
                def.caseSensitivity = ((caseSensitivity.compare("true", Qt::CaseInsensitive) == 0)?Qt::CaseSensitive:Qt::CaseInsensitive);
                def.defaultExtensions = defaultExtensions.split(',');

                // Iterate thru tokens
                if (language_node.childNodes().count() == 1)
                {
                    QDomNode tokens_node = language_node.childNodes().at(0);

                    if (tokens_node.nodeName() == "tokens")
                    {
                        for(int tokenIndex = 0; tokenIndex < tokens_node.childNodes().count(); tokenIndex++)
                        {
                            const QDomNode token_node = tokens_node.childNodes().at(tokenIndex);

                            if (token_node.nodeName() != "token")
                            {
                                continue;
                            }

                            const QString tokenName = token_node.attributes().namedItem("Name").nodeValue();
                            const QString tokenStartString = token_node.attributes().namedItem("StartString").nodeValue();
                            const QString tokenEndString = token_node.attributes().namedItem("EndString").nodeValue();
                            const QString tokenTokenString = token_node.attributes().namedItem("TokenString").nodeValue();
                            const QString searchEndStringLast = token_node.attributes().namedItem("SearchEndStringLast").nodeValue();
                            const QString tokenImmediateStart = token_node.attributes().namedItem("ImmediateStart").nodeValue();
                            const QString tokenOnlyStartTag = token_node.attributes().namedItem("OnlyStartTag").nodeValue();
                            QString tokenNestedTokens;
                            QString tokenNestedTokensRequireAll;
                            QString tokenNestedTokensInSameOrder;

                            if (token_node.namedItem("nested_tokens").isElement())
                            {
                                const QDomNode nestedTokens_node = token_node.namedItem("nested_tokens");

                                tokenNestedTokens = nestedTokens_node.attributes().namedItem("names").nodeValue();
                                tokenNestedTokensRequireAll = nestedTokens_node.attributes().namedItem("require_all").nodeValue();
                                tokenNestedTokensInSameOrder = nestedTokens_node.attributes().namedItem("require_in_same_order").nodeValue();
                            }

                            QTextParserLanguageDefinitionToken token;
                            token.name = tokenName;
                            token.startString = QRegExp(tokenStartString, def.caseSensitivity);
                            token.endString = QRegExp(tokenEndString, def.caseSensitivity);
                            token.tokenString = QRegExp(tokenTokenString, def.caseSensitivity);
                            token.searchEndStringLast = (searchEndStringLast.compare("true", Qt::CaseInsensitive) == 0);
                            token.immediateStartString = (tokenImmediateStart.compare("true", Qt::CaseInsensitive) == 0);
                            token.onlyStartTag = (tokenOnlyStartTag.compare("true", Qt::CaseInsensitive) == 0);

                            tmpNestedTokens.append(tokenNestedTokens);
                            def.tokens.append(token);
                        }
                    }
                }

                for(int target = 0; target < def.tokens.count(); target++)
                {
                    QStringList nestedTokens = tmpNestedTokens[target].split(",", QString::SkipEmptyParts);

                    if (nestedTokens.isEmpty())
                    {
                        continue;
                    }

                    for(int source = 0; source < def.tokens.count(); source++)
                    {
                        if (source == target)
                        {
                            continue;
                        }

                        if (nestedTokens.contains(def.tokens[source].name))
                        {
                            def.tokens[target].nestedTokens.append(source);
                        }
                    }
                }

                for(const QString &tokenStr: startsWith.split(','))
                {
                    bool found = false;

                    for(int c = 0; c < def.tokens.count(); c++)
                    {
                        const QTextParserLanguageDefinitionToken &token = def.tokens.at(c);

                        if (token.name == tokenStr)
                        {
                            def.startsWith.append(c);

                            found = true;
                        }
                    }

                    if (found == false)
                    {
                        qDebug() << "Parser error. Can\'t find token(" << tokenStr << "). File:" << __FILE__ << ", line:" << __LINE__;
                    }
                }

                languageDefinitions.append(def);
            }
            else
            {
                qDebug() << "XML root tag is not language, but" << ("[" + language_node.nodeName() + "]") << "for file" << l_file;
            }
        }
        else
        {
            qDebug() << "There are" << doc.childNodes().count() << "tags in XML root. There should be only 1. For file" << l_file;
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

QTextParserElements QTextParser::parseFile(const QString &fileName)
{
    QTextParserElements ret;
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
            line.text = ts.readLine();
            line.type = QTextParserLine::QTextParserLineTypeCRLFEndLine;
            fileLines.append(line);
        }

        file.close();

        QString fileExtension = finfo.suffix();

        setTextTypeByFileExtension(fileExtension);

        ret = parseTextLines(fileLines);
    }

    return ret;
}

QTextParserElements QTextParser::parseText(const QString &text, const QString &fileExt)
{
    QTextParserElements ret;
    QTextParserLines fileLines;

    setTextTypeByFileExtension(fileExt);

    for(const QString &curline: text.split(QRegExp("(\r\n|\n\r|\r|\n)")))
    {
        QTextParserLine line;
        line.text = curline;
        line.type = QTextParserLine::QTextParserLineTypeCRLFEndLine;
        fileLines.append(line);
    }

    fileLines.last().type = QTextParserLine::QTextParserLineTypeNoEndLine;

    ret = parseTextLines(fileLines);

    return ret;
}

QTextParserElements QTextParser::parseTextLines(const QTextParserLines &lines)
{
    QTextParserElements ret;

    this->lines = lines;

    if (lines.count() <= 0)
    {
        return ret;
    }

    int cur_lines = 0;
    int cur_column = 0;

    int end_lines = lines.count() - 1;
    int end_column = lines.at(0).text.length();

    while(true)
    {
        if (!findFirstElement(lines, cur_lines, cur_column, language.startsWith, -1))
        {
            break;
        }

        QTextParserElement token = parseElement(lines, language.startsWith, cur_lines, cur_column, end_lines, end_column);

        if (token.m_Type < 0)
        {
            qDebug("Parser error. File: %s, line: %u", __FILE__, __LINE__);
            break;
        }

        ret.append(token);
    }

    return ret;
}

const QTextParserLanguageDefinition &QTextParser::getLanguage() const
{
    return language;
}

QTextParserElement QTextParser::parseElement(const QTextParserLines &lines, const QVector<int> &tokens, int &start_line, int &start_column, int end_line, int end_column, int end_token)
{
    QTextParserElement ret;
    bool found;

    const int orig_start_line = start_line;
    const int orig_start_column = start_column;

    found = findFirstElement(lines, start_line, start_column, tokens, end_token);

    if ((found == false)||(start_line > end_line)||((start_line == end_line)&&(start_column >= end_column)))
    {
        return ret;
    }

    const QVector<QTextParserLanguageDefinitionToken> &tokenList = language.tokens;

    if (end_token >= 0)
    {
        /*if (tokenKeyList.count() <= end_token)
        {
            qDebug() << "tokens.key count("<< tokenKeyList.count() << ") is too low. At least" << (end_token + 1) << "needed. File:" << __FILE__ << ", line:" << __LINE__;
            return ret;
        }*/

        if (tokenList[end_token].searchEndStringLast == false)
        {
            const QRegExp &reg = tokenList[end_token].endString;
            int index = reg.indexIn(lines.at(start_line).text, start_column);

            if (index == start_column)
            {
                return ret;
            }
        }
    }

    for(const int &nToken: tokens)
    {
        const QTextParserLanguageDefinitionToken &token = tokenList.at(nToken);

        if ((!token.startString.isEmpty())&&(!token.endString.isEmpty())&&(token.tokenString.isEmpty()))
        {
            const QRegExp &reg = token.startString;
            int index = reg.indexIn(lines.at(start_line).text, start_column);

            if (index == start_column)
            {
                if (token.immediateStartString)
                {
                    ret.m_StartLine = orig_start_line;
                    ret.m_StartColumn = orig_start_column;
                }
                else
                {
                    ret.m_StartLine = start_line;
                    ret.m_StartColumn = start_column;
                }

                start_column += reg.cap().length();

                if (tokenList[nToken].onlyStartTag == true)
                {
                    ret.m_EndLine = start_line;
                    ret.m_EndColumn = start_column;
                }

                while(1)
                {
                    QTextParserElement child = parseElement(lines, token.nestedTokens, start_line, start_column, end_line, end_column, nToken);

                    if (child.m_Type == -1)
                    {
                        break;
                    }

                    ret.m_ChildElements.append(child);
                }

                const QRegExp &reg = tokenList[nToken].endString;
                int index = reg.indexIn(lines.at(start_line).text, start_column);

                if (index == start_column)
                {
                    if (tokenList[nToken].onlyStartTag == false)
                    {
                        start_column += reg.cap().count();
                        ret.m_EndLine = start_line;
                        ret.m_EndColumn = start_column;
                    }

                    ret.m_Type = nToken;
#ifdef DEBUG_QTEXTPARSER
                    ret.m_TypeDebug = tokenList[nToken].name;
#endif
                }
                else
                {
                    ret.m_Text = "End segment NOT found!";
                    ret.m_Type = -1;
#ifdef DEBUG_QTEXTPARSER
                    ret.m_TypeDebug = "Error -1";
#endif
                }
                break;
            }
        }
        else if ((token.startString.isEmpty())&&(token.endString.isEmpty())&&(token.tokenString.isEmpty())&&(token.nestedTokens.count() > 0)&&(end_token >= 0))
        {
            if (token.immediateStartString)
            {
                ret.m_StartLine = orig_start_line;
                ret.m_StartColumn = orig_start_column;
            }
            else
            {
                ret.m_StartLine = start_line;
                ret.m_StartColumn = start_column;
            }

            while(1)
            {
                QTextParserElement child = parseElement(lines, token.nestedTokens, start_line, start_column, end_line, end_column, end_token);

                if (child.m_Type == -1)
                {
                    break;
                }

                ret.m_ChildElements.append(child);
            }

            const QRegExp &reg = tokenList[nToken].endString;
            int index = reg.indexIn(lines.at(start_line).text, start_column);

            if (index == start_column)
            {
                start_column += reg.cap().count();

                ret.m_EndLine = start_line;
                ret.m_EndColumn = start_column;
                ret.m_Type = nToken;
#ifdef DEBUG_QTEXTPARSER
                ret.m_TypeDebug = tokenList[nToken].name;
#endif
                break;
            }
            else
            {
                ret.m_Text = "End segment NOT found!";
                ret.m_Type = -1;
#ifdef DEBUG_QTEXTPARSER
                ret.m_TypeDebug = "Error -1";
#endif
            }
        }
        else if ((token.startString.isEmpty())&&(token.endString.isEmpty())&&(!token.tokenString.isEmpty())&&(token.nestedTokens.count() == 0))
        {
            const QRegExp &reg = tokenList[nToken].tokenString;
            int index = reg.indexIn(lines.at(start_line).text, start_column);

            if (index == start_column)
            {
                if (token.immediateStartString)
                {
                    ret.m_StartLine = orig_start_line;
                    ret.m_StartColumn = orig_start_column;
                }
                else
                {
                    ret.m_StartLine = start_line;
                    ret.m_StartColumn = start_column;
                }
                ret.m_Text = reg.cap();

                start_column += reg.cap().count();

                ret.m_EndLine = start_line;
                ret.m_EndColumn = start_column;
                ret.m_Type = nToken;
#ifdef DEBUG_QTEXTPARSER
                ret.m_TypeDebug = tokenList[nToken].name;
#endif
                break;
            }
        }
        else
        {
            qDebug() << "Invalid nested tokens coombination.";
        }
    }

    if (end_token >= 0)
    {
        if (tokenList[end_token].searchEndStringLast == true)
        {
            const QRegExp &reg = tokenList[end_token].endString;
            int index = reg.indexIn(lines.at(start_line).text, start_column);

            if (index == start_column)
            {
                return ret;
            }
        }
    }

    return ret;
}

bool QTextParser::findFirstElement(const QTextParserLines &lines, int &cur_line, int &cur_column, const QVector<int> &tokens, int end_token)
{
    for(int line = cur_line; line < lines.count(); line++)
    {
        bool found;
        int col;

        if (line == cur_line)
        {
            col = cur_column;
        }
        else
        {
            col = 0;
        }

        found = findFirstElement(lines.at(line).text, col, tokens, end_token);

        if (found)
        {
            cur_line = line;
            cur_column = col;

            return true;
        }
    }

    return false;
}

bool QTextParser::findFirstElement(const QString &line, int &cur_column, const QVector<int> &tokens, int end_token)
{
    bool ret = false;

    int closest_index = INT_MAX;

    if (end_token >= 0)
    {
        while(true)
        {
            if (language.tokens.count() <= end_token)
            {
                qDebug() << "tokens.key count("<< language.tokens.count() << ") is too low. At least" << (end_token + 1) << "needed. File:" << __FILE__ << ", line:" << __LINE__;

                break;
            }

            const QRegExp &reg = language.tokens.at(end_token).endString;
            int index = reg.indexIn(line, cur_column);

            if (index < 0)
            {
                break;
            }

            closest_index = index;
            ret = true;

            break;
        }
    }

    for (int c = 0; c < tokens.count(); c++)
    {
        int nToken = tokens.at(c);
        const QTextParserLanguageDefinitionToken &token = language.tokens.at(nToken);

        if ((nToken < 0)||(nToken >= language.tokens.count()))
        {
            qDebug() << "Token out of range(" << nToken << "). File:" << __FILE__ << ", line:" << __LINE__;
            continue;
        }

        if (!token.tokenString.isEmpty())
        {
            const QRegExp &reg = token.tokenString;
            int index = reg.indexIn(line, cur_column);

            if ((index > -1)&&(index < closest_index))
            {
                closest_index = index;
                ret = true;
            }
        }
        else if (!token.startString.isEmpty())
        {
            const QRegExp &reg = token.startString;
            int index = reg.indexIn(line, cur_column);

            if ((index > -1)&&(index < closest_index))
            {
                closest_index = index;
                ret = true;
            }
        }
        else if (token.nestedTokens.count() > 0)
        {
            int tmp_col = cur_column;

            if (findFirstElement(line, tmp_col, token.nestedTokens, -1))
            {
                if ((tmp_col > -1)&&(tmp_col < closest_index))
                {
                    closest_index = tmp_col;
                    ret = true;
                }
            }
        }
        else
        {
            qDebug() << "Parser error. Token(" << nToken << ") has empty tokenString and startString. File:" << __FILE__ << ", line:" << __LINE__;
            continue;
        }
    }

    if (ret)
    {
        cur_column = closest_index;
    }

    return ret;
}
