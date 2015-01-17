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
};

#endif // QTEXTPARSERCOMPAT_H
