#ifndef QTEXTPARSER_H
#define QTEXTPARSER_H

#include <QStringList>
#include <QString>
#include <Qlist>
#include <QHash>

struct QTextParserLanguageDefinitionToken
{
    QString name;
    QString startString;
    QString endString;
    QString tokenString;
    bool ignoreTerminateString;
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

class QTextParser
{
public:
    QTextParser();
    static void loadParserDefinitionsFromDir(const QString &);
    void setTextTypeByFileExtension(const QString &);
    void setTextTypeByLanguageName(const QString &);
    void parseFile(const QString &);
    void parseText(const QString &, const QString &);
    void parseTextLines(const QStringList &);
    int findElement(const QStringList &, int &, int &, const QStringList &, QString &);
    bool parseElement(const QStringList &, int &, int &, const QStringList &);
private:
    QTextParserLanguageDefinition language;
};

#endif // QTEXTPARSER_H
