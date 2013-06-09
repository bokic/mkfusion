#ifndef QTEXTPARSER_H
#define QTEXTPARSER_H

#include <QStringList>
#include <QString>
#include <QVector>
#include <QList>
#include <QHash>

class QTextParser
{
public:
    //enum QTextParserUnderlineType {UnderlineTypeNoUnderline, UnderlineTypeLine, UnderlineTypeWave};
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

    struct QTextParserLine {
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
        bool ignoreTerminateString;
        QVector<int> nestedTokens;
        bool nestedTokensRequireAll;
        bool nestedTokensInSameOrder;
        QTextParserLanguageDefinitionToken() : ignoreTerminateString(false), nestedTokensRequireAll(false), nestedTokensInSameOrder(false) {}
    };

    struct QTextParserLanguageDefinition
    {
        QString languageName;
        Qt::CaseSensitivity caseSensitivity;
        QStringList defaultExtensions;
        QVector<int> startsWith;
        QHash<QString, QTextParserLanguageDefinitionToken> tokens;
        QTextParserLanguageDefinition() : caseSensitivity(Qt::CaseInsensitive) {}
    };

    QTextParser();
    static void loadParserDefinitionsFromDir(const QString &dir);
    void setTextTypeByFileExtension(const QString &fileExt);
    void setTextTypeByLanguageName(const QString &langName);
    QTextParserElements parseFile(const QString &fileName);
    QTextParserElements parseText(const QString &text, const QString &fileExt);
    QTextParserElements parseTextLines(const QTextParserLines &lines);

private:
    QTextParserElement parseElement(const QTextParserLines &lines, const QVector<int> &tokens, int &start_line, int &start_column, int end_line, int end_column, int end_token = -1);
    bool findFirstElement(const QTextParserLines &lines, int &cur_line, int &cur_column, const QVector<int> &tokens, int end_token);
    bool findFirstElement(const QString &line, int &cur_column, const QVector<int> &tokens, int end_token);
    QTextParserLanguageDefinition language;
};

#endif // QTEXTPARSER_H
