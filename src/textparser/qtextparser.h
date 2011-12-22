#ifndef QTEXTPARSER_H
#define QTEXTPARSER_H

#include <QStringList>
#include <QString>
#include <QColor>
#include <QList>
#include <QHash>

class QTextParser
{
public:
    enum QTextParserUnderlineType {UnderlineTypeNoUnderline, UnderlineTypeLine, UnderlineTypeWave};
    enum QTextParserEndLineType {EndLineTypeNoEndLine, EndLineTypeCREndLine, EndLineTypeLFEndLine, EndLineTypeCRLFEndLine, EndLineTypeLFCREndLine};

    struct QTextParserColorItem {
        int index;
        int length;
        QColor foregroundColor;
        QColor backgroundColor;
        QColor underlineColor;
        QTextParserUnderlineType underline;
        QTextParserColorItem() : index(0), length(0), underline(UnderlineTypeNoUnderline) {}
    };

    struct QTextParserLine {
        QString Content;
        QTextParserEndLineType EndLine;
        QList<QTextParserColorItem> ColorItems;
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
        QString textColor;
        QStringList nestedTokens;
        bool nestedTokensRequireAll;
        bool nestedTokensInSameOrder;
        QTextParserLanguageDefinitionToken() : ignoreTerminateString(false), nestedTokensRequireAll(false), nestedTokensInSameOrder(false) {}
    };

    struct QTextParserLanguageDefinition
    {
        QString languageName;
        bool caseSensitivity;
        QStringList defaultExtensions;
        QStringList startsWith;
        QHash<QString, QTextParserLanguageDefinitionToken> tokens;
        QTextParserLanguageDefinition() : caseSensitivity(false) {}
    };

    QTextParser();
    static void loadParserDefinitionsFromDir(const QString &);
    void setTextTypeByFileExtension(const QString &);
    void setTextTypeByLanguageName(const QString &);
    void parseTextLines(QTextParserLines &);
    int findElement(const QTextParserLines &, int &, int &, const QStringList &, QString &);
    bool parseElement(QTextParserLines &, int &, int &, const QStringList &);
private:
    QTextParserLanguageDefinition language;
};

#endif // QTEXTPARSER_H
