#include "qtextparsercompat.h"
#include <QDebug>


QList<QCFParserTag> QTextParserCompat::toOldParser(const QTextParserElements &newParser) const
{
    QList<QCFParserTag> ret;

    convertLinesToText();

    for(const QTextParserElement &element: newParser)
    {
        ret.append(convertElement(element));
    }

    return ret;
}

QCFParserTag QTextParserCompat::convertElement(const QTextParserElement &element) const
{
    QCFParserTag ret;

    const QString &elementType = language.tokens[element.m_Type].name;

    ret.m_Start = convertPosition(element.m_StartLine, element.m_StartColumn);
    ret.m_Length = convertPosition(element.m_EndLine, element.m_EndColumn) - ret.m_Start;

    Q_ASSERT(ret.m_Length > 0);

    ret.m_Name = element.m_Text;
    // TODO: Somehow implement QTextParserCompat::convertElement(m_OtherTag).

    if (elementType == "StartTag")
    {
        ret.m_TagType = CFTagType;

        if (text.at(ret.m_Start + ret.m_Length - 1) == '/')
        {
            ret.m_InlineClosedTag = true;
        }
    }
    else if (elementType == "EndTag")
    {
        ret.m_TagType = EndCFTagType;
    }
    else if (elementType == "Comment")
    {
        ret.m_TagType = CommentTagType;
    }

    for(const QTextParserElement &child: element.m_ChildElements)
    {
        ret.m_Arguments.m_ChildElements.append(convertChildElement(child));
    }

    return ret;
}

QCFParserElement QTextParserCompat::convertChildElement(const QTextParserElement &element) const
{
    QCFParserElement ret;

    Q_UNIMPLEMENTED();

    return ret;
}

int QTextParserCompat::convertPosition(int line, int column) const
{
    int ret = 0;

    if ((line < 0)||(column < 0)||(line >= lines.count()))
    {
        qDebug() << "Invaild position";
        return -1;
    }

    for(int c = 0; c <= line; c++)
    {
        const QString &current_line = lines.at(c).text;
        QTextParserLine::QTextParserLineType current_line_type = lines.at(c).type;

        if (c == line)
        {
            if (column > current_line.count())
            {
                qDebug() << "Invaild position";

                break;
            }

            return ret + column;
        }

        ret += current_line.count();

        switch(current_line_type)
        {
        case QTextParserLine::QTextParserLineTypeNoEndLine:
            break;
        case QTextParserLine::QTextParserLineTypeCREndLine:
        case QTextParserLine::QTextParserLineTypeLFEndLine:
        case QTextParserLine::QTextParserLineTypeCRLFEndLine:
        case QTextParserLine::QTextParserLineTypeLFCREndLine:
            ret += 1;
            break;
        }
    }

    qDebug() << "Invaild position";
    return -1;
}

void QTextParserCompat::convertLinesToText() const
{
    text.clear();

    for(const QTextParserLine &line: lines)
    {
        text.append(line.text);

        switch(line.type)
        {
        case QTextParserLine::QTextParserLineTypeNoEndLine:
            break;
        case QTextParserLine::QTextParserLineTypeCREndLine:
            text.append("\n");
            break;
        case QTextParserLine::QTextParserLineTypeLFEndLine:
            text.append("\r");
            break;
        case QTextParserLine::QTextParserLineTypeCRLFEndLine:
            text.append("\n\r");
            break;
        case QTextParserLine::QTextParserLineTypeLFCREndLine:
            text.append("\r\n");
            break;
        }
    }
}
