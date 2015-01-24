#include "qtextparsercompat.h"
#include <QRegExp>
#include <QDebug>


QList<QCFParserTag> QTextParserCompat::toOldParser(const QTextParserElements &newParser) const
{
    QList<QCFParserTag> ret;

    convertLinesToText();

    for(const QTextParserElement &newElement: newParser)
    {
        QCFParserTag oldElement = convertElement(newElement);

        if ((oldElement.m_TagType == CFTagType)&&(oldElement.m_Name == "cfoutput"))
        {
            oldElement.m_Arguments.m_ChildElements.clear();

            ret.append(oldElement);

            for(QTextParserElement child: newElement.m_ChildElements)
            {
                ret.append(convertElement(child));
            }
        }
        else
        {
            ret.append(oldElement);
        }

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

        QRegExp reg("cf[a-z0-9_]+", language.caseSensitivity);
        int offset = reg.indexIn(text, ret.m_Start);
        if (offset > ret.m_Start)
        {
            ret.m_Name = reg.cap().toLower();
        }

        if (text.at(ret.m_Start + ret.m_Length - 1) == '/')
        {
            ret.m_InlineClosedTag = true;
        }
    }
    else if (elementType == "EndTag")
    {
        ret.m_TagType = EndCFTagType;

        QRegExp reg("cf[a-z0-9_]+", language.caseSensitivity);
        int offset = reg.indexIn(text, ret.m_Start);
        if (offset > ret.m_Start)
        {
            ret.m_Name = reg.cap().toLower();
        }
    }
    else if (elementType == "Comment")
    {
        ret.m_TagType = CommentTagType;
    }
    else if (elementType == "SharpExpression")
    {
        ret.m_TagType = ExpressionTagType;
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

    const QString &elementType = language.tokens[element.m_Type].name;

    if (elementType == "Boolean")
    {
        ret.m_Type = Boolean;
    }
    else if (elementType == "Number")
    {
        ret.m_Type = Number;
    }
    else if (elementType == "String")
    {
        ret.m_Type = String;
    }
    else if (elementType == "Variable")
    {
        ret.m_Type = Variable;
    }
    else if (elementType == "Function")
    {
        ret.m_Type = Function;
    }
    else if (elementType == "Operator")
    {
        ret.m_Type = Operator;
    }
    else if (elementType == "SharpExpression")
    {
        ret.m_Type = SharpExpression;
    }
    else if (elementType == "CodeBlock")
    {
        ret.m_Type = CodeBlock;
    }
    else if (elementType == "Expression")
    {
        ret.m_Type = Expression;
    }
    else if (elementType == "SubExpression")
    {
        ret.m_Type = SubExpression;
    }
    else if (elementType == "Parameters")
    {
        ret.m_Type = Parameters;
    }
    else if (elementType == "Parameter")
    {
        ret.m_Type = Parameter;
    }
    else if (elementType == "CFScript")
    {
        ret.m_Type = CFScript;
    }
    else if (elementType == "CFComment")
    {
        ret.m_Type = CFComment;
    }
    else if (elementType == "CFTagExpression")
    {
        ret.m_Type = CFTagExpression;
    }
    else if (elementType == "CFTagArguments")
    {
        ret.m_Type = CFTagArguments;
    }
    else if (elementType == "CFTagArgument")
    {
        ret.m_Type = CFTagArgument;
    }
    else if (elementType == "ObjectFunction")
    {
        ret.m_Type = ObjectFunction;
    }
    else if (elementType == "VariableMember")
    {
        ret.m_Type = VariableMember;
    }
    else if (elementType == "Keyword")
    {
        ret.m_Type = Keyword;
    }
    else if (elementType == "Error")
    {
        ret.m_Type = Error;
    }
    else if (elementType == "Null")
    {
        ret.m_Type = Null;
    }

    ret.m_Text = element.m_Text;
    ret.m_Position = convertPosition(element.m_StartLine, element.m_StartColumn);
    ret.m_Size = convertPosition(element.m_EndLine, element.m_EndColumn) - ret.m_Position;

    for(const QTextParserElement &child: element.m_ChildElements)
    {
        ret.m_ChildElements.append(convertChildElement(child));
    }

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
