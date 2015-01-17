#include "qtextparsercompat.h"

QList<QCFParserTag> QTextParserCompat::toOldParser(const QTextParserElements &newParser) const
{
    QList<QCFParserTag> ret;

    for(const QTextParserElement &element: newParser)
    {
        ret.append(convertElement(element));
    }

    return ret;
}

QCFParserTag QTextParserCompat::convertElement(const QTextParserElement &element) const
{
    QCFParserTag ret;

    QString elementType = language.tokens.keys().at(element.m_Type);

    if (elementType == "CFScript")
    {
        //ret.m_TagType = ;
    }
    else
    {

    }

    return ret;
}
