/****************************************************************************
**
** Author: Boris Barbulovski(bbarbulovski@gmail.com)
**
** This file is part of the MKFusion(http://mkfusion.bokicsoft.com/ or
** https://sourceforge.net/projects/mkfusion/) project.
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

#ifndef QTEXTPARSER_H
#define QTEXTPARSER_H

#include <QStringList>
#include <QString>
#include <QVector>
#include <QList>
#include <QHash>

#ifdef QCFPARSER_H
#define QTEXTPARSER_COMPATIBILITY
#endif

class QTextParser
{
public:
    enum QTextParserEndLineType {EndLineTypeNoEndLine, EndLineTypeCREndLine, EndLineTypeLFEndLine, EndLineTypeCRLFEndLine, EndLineTypeLFCREndLine};

    struct QTextParserElement
    {
        int m_Type;
        QString m_Text;
        int m_StartLine;
        int m_StartColumn;
        int m_EndLine;
        int m_EndColumn;
        QList<QTextParserElement> m_ChildElements;
#ifdef DEBUG_QTEXTPARSER
        QString m_Debug;
#endif
        QTextParserElement() : m_Type(-1), m_StartLine(-1), m_StartColumn(-1), m_EndLine(-1), m_EndColumn(-1) {}
    };

    typedef QList<QTextParserElement> QTextParserElements;

    struct QTextParserLine
    {
        QString Content;
        QTextParserEndLineType EndLine;
        QTextParserLine() : EndLine(EndLineTypeNoEndLine) {}
    };

    typedef QList<QTextParserLine> QTextParserLines;

    struct QTextParserLanguageDefinitionToken
    {
        QString name;
        QString startString;
        QString endString;
        QString tokenString;
        bool searchEndStringLast; // TODO: Unimplemented yet(greedy/lazy??)
        bool immediateStartString;
        QVector<int> nestedTokens;
        QTextParserLanguageDefinitionToken() : searchEndStringLast(false), immediateStartString(false) {}
    };

    struct QTextParserLanguageDefinition
    {
        QString languageName;
        Qt::CaseSensitivity caseSensitivity;
        QStringList defaultExtensions;
        QVector<int> startsWith;
        QHash<QString, QTextParserLanguageDefinitionToken> tokens;
        QTextParserLanguageDefinition() : languageName(), caseSensitivity(Qt::CaseInsensitive), defaultExtensions(), startsWith(), tokens() {}
    };

    QTextParser();
    static void loadParserDefinitionsFromDir(const QString &dir);
    void setTextTypeByFileExtension(const QString &fileExt);
    void setTextTypeByLanguageName(const QString &langName);
    QTextParserElements parseFile(const QString &fileName);
    QTextParserElements parseText(const QString &text, const QString &fileExt);
    QTextParserElements parseTextLines(const QTextParserLines &lines);
    const QTextParserLanguageDefinition &getLanguage() const;

protected:
    QTextParserElement parseElement(const QTextParserLines &lines, const QVector<int> &tokens, int &start_line, int &start_column, int end_line, int end_column, int end_token = -1);
    bool findFirstElement(const QTextParserLines &lines, int &cur_line, int &cur_column, const QVector<int> &tokens, int end_token);
    bool findFirstElement(const QString &line, int &cur_column, const QVector<int> &tokens, int end_token);
    QTextParserLanguageDefinition language;
};

#endif // QTEXTPARSER_H
