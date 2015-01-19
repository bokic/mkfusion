#ifndef QTEXTPARSERCOMPAT_H
#define QTEXTPARSERCOMPAT_H

#include "qtextparser.h"
#include "qcfparser.h"


class QTextParserCompat : public QTextParser
{
public:
    QList<QCFParserTag> toOldParser(const QTextParserElements &newParser) const;

protected:
    QCFParserTag convertElement(const QTextParserElement &element) const;
    QCFParserElement convertChildElement(const QTextParserElement &element) const;
    int convertPosition(int line, int column) const;
    void convertLinesToText() const;

    mutable QString text;
};

#endif // QTEXTPARSERCOMPAT_H
