#include "qcfparser.h"
#include "qcf8.h"

#include <QTextStream>
#include <QFileInfo>
#include <QDateTime>
#include <QString>
#ifdef QT_DEBUG
#include <QDebug>
#endif
#include <QFile>

/*
  (0) comment inside cftags.
  (0) cfscript
    * End of cfscript: </cf
  (5) cftagarguments
    * End of cfarguments: > or />
  (3) cftagargument
    * End of cfargument:
  (0) expression
  (0) object member function
  (0) function
    * End of function name chars are: tab, space, newline, (
   ** Ilegal characters inside brackets <, /, >
  (3) variable
    * End of variable name chars are: tab, space, newline, [ , (, -, +, *, /
  (2) operator
  (3) string
  (5) numerical
  (0) parametars
  (0) parametar
  */

QCFParser::QCFParser()
    : QObject()
    , m_FileSize(0)
    , m_FileModifyDateTime(0)
    , m_InsideCFScript(false)
    , m_FileType(QCFParserTemplateFile)
    , m_CFTagsDef(QCF8::generateCFTags())
    , m_CFFunctionsDef(QCF8::generateCFFunctions())
    , m_ErrorPosition(0)
    , m_Mode(FullParseMode)
{
}

QCFParser::QCFParser(QCFParserMode mode, QCFParserFileType filetype)
    : QObject()
    , m_FileSize(0)
    , m_FileModifyDateTime(0)
    , m_InsideCFScript(false)
    , m_FileType(filetype)
    , m_CFTagsDef(QCF8::generateCFTags())
    , m_CFFunctionsDef(QCF8::generateCFFunctions())
    , m_ErrorPosition(0)
    , m_Mode(mode)
{
}

bool QCFParser::TrimCFCode(const QString &p_Text, int &p_Offset)
{
    int l_Len = p_Text.length();
    ushort l_ch;

    forever
    {
        if (p_Offset >= l_Len)
        {
            return true;
        }

        l_ch = p_Text.at(p_Offset).unicode();
        if ((l_ch == ' ')||(l_ch == '\t')||(l_ch == '\r')||(l_ch == '\n'))
        {
            p_Offset++;
            continue;
        }
        break;
    }

    return false;
}

bool QCFParser::isValidVarChar(const QString &p_Text, int index)
{
    if ((index < 0)||(index >= p_Text.count()))
    {
        return false;
    }

    ushort ch = p_Text.at(index).unicode();

    if (((ch >= 'A')&&(ch <= 'Z'))||((ch >= 'a')&&(ch <= 'z'))||((ch >= '0')&&(ch <= '9'))||(ch == '_'))
    {
        return true;
    }

    return false;
}

QCFParserElement QCFParser::ParseCFCode(const QString &p_Text, const qint32 p_Offset, const QCFParserElementType p_ElementType, QCFParserElement *parent = 0)
{
    QCFParserElement ret;
    QCFParserElement child;
    QString str;
    ushort ch, ch2;
    ret.m_Type = p_ElementType;
    int l_Offset = p_Offset;

    //if ((p_ElementType != Expression)&&(TrimCFCode(p_Text, l_Offset)))
    if (TrimCFCode(p_Text, l_Offset))
    {
        ret.m_Type = Error;
        ret.m_Position = l_Offset - 1;
        ret.m_Text = tr("End of file found.");
        return ret;
    }

    ret.m_Position = l_Offset;

    switch(p_ElementType)
    {
    case CFTagExpression:
        ch = p_Text.at(l_Offset).unicode();

        if (ch == '>')
        {
            ret.m_Size = l_Offset - p_Offset;
            return ret;
        }

        if (ch == '/')
        {
            // TODO: Missing len check.
            if (l_Offset + 1 >= p_Text.length())
            {
                ret.m_Type = Error;
                ret.m_Text = tr("'>' Missing.");
                return ret;
            }

            ch2 = p_Text.at(l_Offset + 1).unicode();
            if (ch2 == '>')
            {
                ret.m_Size = l_Offset - p_Offset + 1;
                return ret;
            }
            else
            {
                ret.m_Type = Error;
                ret.m_Text = tr("'>' Missing, and something else found.");
                return ret;
            }
        }

        child = ParseCFCode(p_Text, l_Offset, Expression, &ret);
        if (child.m_Type == Error)
        {
            return child;
        }
        ret.m_ChildElements.append(child);
        ret.m_Size = child.m_Size;
        //l_Offset = child.m_Position + child.m_Size;
        break;
    case CFTagArguments:
        while ( l_Offset < p_Text.length() )
        {
            if (TrimCFCode(p_Text, l_Offset))
            {
                ret.m_Type = Error;
                ret.m_Position = l_Offset - 1;
                ret.m_Text = tr("cftag not closed.");
                return ret;
            }
            ch = p_Text.at(l_Offset).unicode();

            if (ch == '>')
            {
                ret.m_Position = p_Offset;
                ret.m_Size = l_Offset - p_Offset;
                return ret;
            }

            if (ch == '/')
            {
                if (l_Offset + 1 >= p_Text.length())
                {
                    ret.m_Type = Error;
                    ret.m_Text = tr("'>' Missing.");
                    return ret;
                }

                ch2 = p_Text.at(l_Offset + 1).unicode();
                if (ch2 == '>')
                {
                    ret.m_Position = p_Offset;
                    ret.m_Size = l_Offset - p_Offset;
                    return ret;
                }
                else
                {
                    ret.m_Type = Error;
                    ret.m_Text = tr("'>' Missing, something else found.");
                    return ret;
                }
            }

            child = ParseCFCode(p_Text, l_Offset, CFTagArgument, &ret);
            if (child.m_Type == Error)
            {
                return child;
            }
            ret.m_ChildElements.append(child);
            l_Offset = child.m_Position + child.m_Size;
        }

        ret.m_Type = Error;
        ret.m_Position = p_Text.length();
        ret.m_Text = tr("cftag not closed.");
        break;
    case CFTagArgument:
        int l_NotOperatorFirst;
        int lastElementFound;
        int index;

        index = 0;
        l_NotOperatorFirst = 0;
        lastElementFound = l_Offset;

        for (int c = l_Offset; c < p_Text.length(); )
        {
            if (TrimCFCode(p_Text, c))
            {
                ret.m_Type = Error;
                ret.m_Position = l_Offset - 1;
                ret.m_Text = tr("End of file found.");
                return ret;
            }
            ch = p_Text.at(c).unicode();

            if (ch == '>')
            {
                ret.m_Size = lastElementFound - ret.m_Position;
                return ret;
            }

            if (ch == '/')
            {
                if (c + 1 >= p_Text.length())
                {
                    ret.m_Type = Error;
                    ret.m_Size = c + 1;
                    ret.m_Text = tr("'>' Missing.");
                    return ret;
                }

                ch2 = p_Text.at(c + 1).unicode();
                if (ch2 == '>')
                {
                    ret.m_Size = lastElementFound - ret.m_Position;
                    return ret;
                }
                else
                {
                    ret.m_Type = Error;
                    ret.m_Size = c + 1;
                    ret.m_Text = tr("'>' Missing.");
                    return ret;
                }
            }

            if (ch == '<')
            {
                child = ParseCFCode(p_Text, c, CFComment, &ret);
                if (child.m_Type == Error)
                {
                    return child;
                }
                ret.m_ChildElements.append(child);
                lastElementFound = child.m_Position + child.m_Size;
                c = child.m_Position + child.m_Size;
                continue;
            }

            if ((index + l_NotOperatorFirst) % 2 == 0)
            {
                if ((ch == '\'')||(ch == '\"'))
                    child = ParseCFCode(p_Text, c, String, &ret);
                else if (((ch >= '0')&&(ch <= '9'))||(ch == '-')||(ch == '+'))
                    child = ParseCFCode(p_Text, c, Number, &ret);
                else if (ch == '#')
                    child = ParseCFCode(p_Text, c, SharpExpression, &ret);
                else
                    child = ParseCFCode(p_Text, c, Variable, &ret);
            }
            else
            {
                child = ParseCFCode(p_Text, c, Operator, &ret);
                if (child.m_Type == Error)
                {
                    ret.m_Size = lastElementFound - ret.m_Position;
                    return ret;
                }
            }

            if ((index == 0)&&(child.m_Type == Operator)&&(child.m_Text == "NOT"))
            {
                l_NotOperatorFirst = 1;
            }

            if (child.m_Type == Error)
            {
                return child;
            }

            if (((index+l_NotOperatorFirst) % 2 == 1)&&(child.m_Type != Operator))
            {
                child = ret.m_ChildElements.last();
                ret.m_Size = (child.m_Position + child.m_Size) - ret.m_Position;
                break;
            }
            ret.m_ChildElements.append(child);
            lastElementFound = child.m_Position + child.m_Size;
            c = child.m_Position + child.m_Size;
            index++;
        }

        ret.m_Type = Error;
        ret.m_Position = p_Text.length();
        ret.m_Text = tr("cftag not closed.");
        break;
    case Variable:
        for (int c = l_Offset; c < p_Text.length(); c++)
        {
            ch = p_Text.at(c).unicode();

            if ((l_Offset == c)&&(((ch >= '0')&&(ch <= '9'))||(ch == '-')||(ch == '+')))
            {
                return ParseCFCode(p_Text, l_Offset, Number, &ret);
            }

            if ((l_Offset == c)&&((ch == '*')||(ch == '/')||(ch == '\\')||(ch == '^')||(ch == '&')||(ch == '=')))
            {
                return ParseCFCode(p_Text, l_Offset, Operator, &ret);
            }

            if ((l_Offset == c)&&((ch =='\'')||(ch =='\"')))
            {
                return ParseCFCode(p_Text, l_Offset, String, &ret);
            }

            if ((l_Offset == c)&&(ch =='#'))
            {
                return ParseCFCode(p_Text, l_Offset, SharpExpression, &ret);
            }

            if ((ch =='(')||(ch =='{'))
            {
                str = p_Text.mid(p_Offset, c - p_Offset).trimmed();

                if (
                    (str.compare("eq", Qt::CaseInsensitive) == 0)||
                    (str.compare("is", Qt::CaseInsensitive) == 0)||
                    (str.compare("neq", Qt::CaseInsensitive) == 0)||
                    (str.compare("gt", Qt::CaseInsensitive) == 0)||
                    (str.compare("ge", Qt::CaseInsensitive) == 0)||
                    (str.compare("gte", Qt::CaseInsensitive) == 0)||
                    (str.compare("lt", Qt::CaseInsensitive) == 0)||
                    (str.compare("le", Qt::CaseInsensitive) == 0)||
                    (str.compare("lte", Qt::CaseInsensitive) == 0)||
                    (str.compare("not", Qt::CaseInsensitive) == 0)||
                    (str.compare("and", Qt::CaseInsensitive) == 0)||
                    (str.compare("or", Qt::CaseInsensitive) == 0)||
                    (str.compare("xor", Qt::CaseInsensitive) == 0)||
                    (str.compare("eqv", Qt::CaseInsensitive) == 0)||
                    (str.compare("imp", Qt::CaseInsensitive) == 0)||
                    (str.compare("mod", Qt::CaseInsensitive) == 0)||
                    (str.compare("equal", Qt::CaseInsensitive) == 0)||
                    (str.compare("contains", Qt::CaseInsensitive) == 0)
                )
                {
                    ret.m_Type = Operator;
                    ret.m_Text = str;
                    ret.m_Size = c - p_Offset;

                    return ret;
                }
                else if (
                    (str.compare("true", Qt::CaseInsensitive) == 0)||
                    (str.compare("false", Qt::CaseInsensitive) == 0)||
                    (str.compare("yes", Qt::CaseInsensitive) == 0)||
                    (str.compare("no", Qt::CaseInsensitive) == 0)
                )
                {
                    ret.m_Type = Boolean;
                    ret.m_Text = str;
                    ret.m_Size = c - p_Offset;

                    return ret;
                }
                else if (
                    (str.compare("var", Qt::CaseInsensitive) == 0)||
                    (str.compare("function", Qt::CaseInsensitive) == 0)||
                    (str.compare("return", Qt::CaseInsensitive) == 0)||
                    (str.compare("if", Qt::CaseInsensitive) == 0)||
                    (str.compare("else", Qt::CaseInsensitive) == 0)||
                    (str.compare("try", Qt::CaseInsensitive) == 0)||
                    (str.compare("catch", Qt::CaseInsensitive) == 0)||
                    ((str.compare("this", Qt::CaseInsensitive) == 0)&&(m_FileType == QCFParserComponentFile))
                )
                {
                    ret.m_Type = Keyword;
                    ret.m_Text = str;
                    ret.m_Size = c - p_Offset;

                    return ret;
                }

                if (ch =='(')
                {
                    return ParseCFCode(p_Text, l_Offset, Function, &ret);
                }
                else
                {
                    ret.m_Type = Variable;
                    ret.m_Text = str;
                    ret.m_Size = c - p_Offset;

                    return ret;
                }
            }

            if ((ch == '[')||(ch == '.'))
            {
                ret.m_Text = p_Text.mid(l_Offset, c - l_Offset).trimmed();

                if ((ret.m_Text.compare("this", Qt::CaseInsensitive) == 0)&&(m_FileType == QCFParserComponentFile))
                {
                    ret.m_Type = Keyword;
                }

                if ((parent)&&(parent->m_Type == VariableMember))
                {
                    ret.m_Size = c - ret.m_Position;

                    return ret;
                }

                do
                {
                    child = ParseCFCode(p_Text, c, VariableMember, &ret);

                    if (child.m_Type == Error)
                    {
                        return child;
                    }

                    ret.m_ChildElements.append(child);

                    c = child.m_Position + child.m_Size;

                    if (p_Text.length() > c)
                    {
                        ch = p_Text.at(c).unicode();
                    }
                    else
                    {
                        ch = 0;
                    }

                }
                while((ch == '[')||(ch == '.'));

                ret.m_Size = c - ret.m_Position;

                return ret;
            }

            if (ch == ' ')
            {
                int start_bracket = p_Text.indexOf("(", c);

                if ((start_bracket > c)&&(p_Text.mid(c, start_bracket - c).trimmed() == "")) // TODO: Optimize me when possible.
                {
                    continue;
                }

                start_bracket = p_Text.indexOf("[", c);

                if ((start_bracket > c)&&(p_Text.mid(c, start_bracket - c).trimmed() == "")) // TODO: Optimize me when possible.
                {
                    continue;
                }
            }

            if ((ch == ' ')||(ch == '\r')||(ch == '\n')||(ch == '\'')||(ch == '\"')||(ch == '=')||(ch == '&')||(ch == '#')||(ch == '/')||(ch == ')')||(ch == ']')||(ch == ',')||(ch == '+')||(ch == '-')||(ch == '*')||(ch == '<')||(ch == '>')||(ch == ';')) // TODO: Add other operators
            {
                if (c - l_Offset == 0)
                {
                    ret.m_Type = Error;
                    ret.m_Position = c;
                    ret.m_Size = 1;
                    ret.m_Text = tr("Invalid variable name.");
                    return ret;
                }
                ret.m_Position = l_Offset;
                ret.m_Size = c - l_Offset;
                ret.m_Text = p_Text.mid(l_Offset, c - l_Offset).trimmed();
                if (
                    (ret.m_Text.compare("eq", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("is", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("neq", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("gt", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("ge", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("gte", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("lt", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("le", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("lte", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("not", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("and", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("or", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("xor", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("eqv", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("imp", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("mod", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("equal", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("contains", Qt::CaseInsensitive) == 0)
                )
                {
                    ret.m_Type = Operator;
                }
                else if (
                    (ret.m_Text.compare("true", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("false", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("yes", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("no", Qt::CaseInsensitive) == 0)
                )
                {
                    ret.m_Type = Boolean;
                }
                else if (
                    (ret.m_Text.compare("var", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("function", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("return", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("if", Qt::CaseInsensitive) == 0)||
                    (ret.m_Text.compare("else", Qt::CaseInsensitive) == 0)||
                    ((ret.m_Text.compare("this", Qt::CaseInsensitive) == 0)&&(m_FileType == QCFParserComponentFile))
                )
                {
                    ret.m_Type = Keyword;
                }

                return ret;
            }
        }
        //ret.m_Type = Error;
        //ret.m_Size = 1;
        //ret.m_Text = tr("Variable name not set.");
        ret.m_Size = p_Text.length() - l_Offset;
        ret.m_Text = p_Text.mid(l_Offset, ret.m_Size);

        if (
            (ret.m_Text.compare("eq", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("is", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("neq", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("gt", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("ge", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("gte", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("lt", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("le", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("lte", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("not", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("and", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("or", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("xor", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("eqv", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("imp", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("mod", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("equal", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("contains", Qt::CaseInsensitive) == 0)
        )
        {
            ret.m_Type = Operator;
        }
        else if (
            (ret.m_Text.compare("true", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("false", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("yes", Qt::CaseInsensitive) == 0)||
            (ret.m_Text.compare("no", Qt::CaseInsensitive) == 0)
        )
        {
            ret.m_Type = Boolean;
        }
        else if (
            (ret.m_Text.compare("var", Qt::CaseInsensitive) == 0)||
            ((ret.m_Text.compare("this", Qt::CaseInsensitive) == 0)&&(m_FileType == QCFParserComponentFile))
        )
        {
            ret.m_Type = Keyword;
        }

        break;
    case Number:
        bool comma;
        int signOffset;

        ch = p_Text.at(l_Offset).unicode();
        if (((ch < '0')||(ch > '9'))&&(ch !='-')&&(ch !='+'))
        {
            ret.m_Type = Error;
            ret.m_Position = l_Offset;
            ret.m_Text = tr("Element not number.");
            return ret;
        }

        comma = false;
        signOffset = l_Offset;

        for (int c = l_Offset; c < p_Text.length(); c++)
        {
            ch = p_Text.at(c).unicode();

            if ((c == signOffset)&&((ch == '-')||(ch == '+')))
            {
                continue;
            }

            if ((ch == '.')&&(comma == false))
            {
                comma = true;
                continue;
            }

            if ((ch < '0')||(ch > '9'))
            {
                ret.m_Size = c - l_Offset;
                ret.m_Text = p_Text.mid(l_Offset, c - l_Offset);
                if ((ret.m_Text == "-")||(ret.m_Text == "+"))
                {
                    ret.m_Type = Operator;
                }
                return ret;
            }
        }
        ret.m_Type = Error;
        break;
    case String:
        ushort stringType;
        stringType = 0;

        for (int c = l_Offset; c < p_Text.length(); c++)
        {
            ch = p_Text.at(c).unicode();

            if (c == l_Offset)
            {
                stringType = ch;

                if ((ch != '\'')&&(ch != '\"'))
                {
                    ret.m_Type = Error;
                    ret.m_Text = tr("String not start with ['] or [\"].");
                    return ret;
                }
            }
            else
            {
                if (ch == '#')
                {
                    if (p_Text.length() <= c)
                    {
                        ret.m_Type = Error;
                        ret.m_Position = c;
                        ret.m_Size = 1;
                        ret.m_Text = tr("# not closed.");
                        return ret;
                    }

                    if (p_Text.at(c + 1) == '#')
                    {
                        str.append(QChar(ch));
                        c++;
                        continue;
                    }
                    else
                    {
                        if (!str.isEmpty())
                        {
                            child = QCFParserElement();
                            child.m_Position = c - str.length();
                            child.m_Size = str.length();
                            child.m_Type = String;
                            child.m_Text = str;
                            ret.m_ChildElements.append(child);
                            str.clear();
                        }

                        child = ParseCFCode(p_Text, c, SharpExpression, &ret);
                        ret.m_ChildElements.append(child);
                        c = child.m_Position + child.m_Size - 1;
                    }
                }
                else
                {
                    if (ch == stringType)
                    {
                        ret.m_Size = c - l_Offset + 1;

                        if (ret.m_ChildElements.count() == 0)
                        {
                            ret.m_Text = str;
                        }
                        else
                        {
                            ret.m_Text = "";
                            if (!str.isEmpty())
                            {
                                child = QCFParserElement();
                                child.m_Position = c - str.length();
                                child.m_Size = str.length() + 1;
                                child.m_Type = String;
                                child.m_Text = str;
                                ret.m_ChildElements.append(child);
                            }
                        }

                        return ret;
                    }
                    str.append(QChar(ch));
                }
            }
        }
        ret.m_Type = Error;
        ret.m_Size = 1;
        ret.m_Text = tr("String not finished.");
        break;
    case Operator:
        ch = p_Text.at(l_Offset).unicode();

        if ((ch == '=')||(ch == '&')||(ch == '*')||(ch == '/')||(ch == '\\')||(ch == '^')||(ch == '+')||(ch == '-')||(ch == '.'))
        {
            ret.m_Position = l_Offset;
            ret.m_Size = 1;
            ret.m_Text = QChar(ch);
            break;
        }

        if ((p_Text.mid(l_Offset, 2).compare("eq", Qt::CaseInsensitive) == 0)&&(!isValidVarChar(p_Text, l_Offset  + 3)))
        {
            ret.m_Position = l_Offset;
            ret.m_Size = 2;
            ret.m_Text = p_Text.mid(l_Offset, 2).toUpper();
            break;
        }

        if ((p_Text.mid(l_Offset, 3).compare("neq", Qt::CaseInsensitive) == 0)&&(!isValidVarChar(p_Text, l_Offset  + 4)))
        {
            ret.m_Position = l_Offset;
            ret.m_Size = 3;
            ret.m_Text = p_Text.mid(l_Offset, 3).toUpper();
            break;
        }

        if ((p_Text.mid(l_Offset, 3).compare("and", Qt::CaseInsensitive) == 0)&&(!isValidVarChar(p_Text, l_Offset  + 4)))
        {
            ret.m_Position = l_Offset;
            ret.m_Size = 3;
            ret.m_Text = p_Text.mid(l_Offset, 3).toUpper();
            break;
        }
        if ((p_Text.mid(l_Offset, 3).compare("mod", Qt::CaseInsensitive) == 0)&&(!isValidVarChar(p_Text, l_Offset  + 4)))
        {
            ret.m_Position = l_Offset;
            ret.m_Size = 3;
            ret.m_Text = p_Text.mid(l_Offset, 3).toUpper();
            break;
        }

        if ((p_Text.mid(l_Offset, 2).compare("or", Qt::CaseInsensitive) == 0)&&(!isValidVarChar(p_Text, l_Offset  + 3)))
        {
            ret.m_Position = l_Offset;
            ret.m_Size = 2;
            ret.m_Text = p_Text.mid(l_Offset, 2).toUpper();
            break;
        }

        if ((p_Text.mid(l_Offset, 3).compare("xor", Qt::CaseInsensitive) == 0)&&(!isValidVarChar(p_Text, l_Offset  + 4)))
        {
            ret.m_Position = l_Offset;
            ret.m_Size = 3;
            ret.m_Text = p_Text.mid(l_Offset, 3).toUpper();
            break;
        }

        if ((p_Text.mid(l_Offset, 3).compare("eqv", Qt::CaseInsensitive) == 0)&&(!isValidVarChar(p_Text, l_Offset  + 4)))
        {
            ret.m_Position = l_Offset;
            ret.m_Size = 3;
            ret.m_Text = p_Text.mid(l_Offset, 3).toUpper();
            break;
        }

        if ((p_Text.mid(l_Offset, 3).compare("imp", Qt::CaseInsensitive) == 0)&&(!isValidVarChar(p_Text, l_Offset  + 4)))
        {
            ret.m_Position = l_Offset;
            ret.m_Size = 3;
            ret.m_Text = p_Text.mid(l_Offset, 3).toUpper();
            break;
        }

        if ((p_Text.mid(l_Offset, 2).compare("is", Qt::CaseInsensitive) == 0)&&(!isValidVarChar(p_Text, l_Offset  + 3)))
        {
            ret.m_Position = l_Offset;
            ret.m_Size = 2;
            ret.m_Text = p_Text.mid(l_Offset, 2).toUpper();
            break;
        }

        if ((p_Text.mid(l_Offset, 5).compare("equal", Qt::CaseInsensitive) == 0)&&(!isValidVarChar(p_Text, l_Offset  + 6)))
        {
            ret.m_Position = l_Offset;
            ret.m_Size = 5;
            ret.m_Text = p_Text.mid(l_Offset, 5).toUpper();
            break;
        }

        if ((p_Text.mid(l_Offset, 3).compare("not", Qt::CaseInsensitive) == 0)&&(!isValidVarChar(p_Text, l_Offset  + 4)))
        {
            ret.m_Position = l_Offset;
            ret.m_Size = 3;
            ret.m_Text = p_Text.mid(l_Offset, 3).toUpper();
            break;
        }

        if ((p_Text.mid(l_Offset, 8).compare("contains", Qt::CaseInsensitive) == 0)&&(!isValidVarChar(p_Text, l_Offset  + 9)))
        {
            ret.m_Position = l_Offset;
            ret.m_Size = 8;
            ret.m_Text = p_Text.mid(l_Offset, 8).toUpper();
            break;
        }

        ret.m_Type = Error;
        break;
    case SharpExpression:
        if (p_Text.at(l_Offset) != '#')
        {
            ret.m_Type = Error;
            ret.m_Position = l_Offset;
            ret.m_Text = tr("SharpExpression doesn't start with '#'.");
            break;
        }

        child = ParseCFCode(p_Text, l_Offset + 1, Expression, &ret);
        if (child.m_Type == Error)
        {
            ret = child;
            break;
        }

        if (p_Text.at(l_Offset + child.m_Size + 1) != '#')
        {
            ret.m_Type = Error;
            ret.m_Position = l_Offset;
            ret.m_Text = tr("SharpExpression doesn't end with '#'.");
            break;
        }

        ret.m_Size = child.m_Size + 2;
        ret.m_ChildElements.append(child);
        break;
    case CodeBlock:
        if (p_Text.at(l_Offset) != '{')
        {
            ret.m_Type = Error;
            ret.m_Position = l_Offset;
            ret.m_Text = tr("CodeBlock doesn't start with '{'.");
            break;
        }

        do
        {
            child = ParseCFCode(p_Text, l_Offset + 1, Expression, &ret);
            if (child.m_Type == Error)
            {
                ret = child;
                break;
            }

            if (child.m_Size > 0)
            {
                ret.m_ChildElements.append(child);
            }

            l_Offset = child.m_Position + child.m_Size;

        }
        while (p_Text.at(l_Offset) != '}');

        ret.m_Size = (child.m_Position + child.m_Size) - ret.m_Position + 1;
        break;
    case Expression:
        int c;
        char nextch;

        ret.m_Position = p_Offset;
        c = l_Offset;

        ret.m_Size = 0;

        while( c < p_Text.length())
        {
            if (TrimCFCode(p_Text, c))
            {
                ret.m_Type = Error;
                ret.m_Position = l_Offset - 1;
                ret.m_Text = tr("End of file found.");
                return ret;
            }

            ch = p_Text.at(c).unicode();

            if(c + 1 < p_Text.length())
            {
                nextch = p_Text.at(c + 1).toLatin1();
            }
            else
            {
                nextch = 0;
            }

            if ((ch == '<')||((ch == '/')&&(nextch == '>'))||(ch == '>'))
            {
                ret.m_Size = c - p_Offset;
                break;
            }
            else if (ch == ']')
            {
                ret.m_Size = c - p_Offset;
                break;
            }
            else if (ch == ',')
            {
                ret.m_Size = c - p_Offset;
                break;
            }
            else if (ch == '}')
            {
                //if (m_InsideCFScript)
                //{
                ret.m_Size = c - p_Offset;
                break;
                /*}
                else
                {
                    ret.m_Type = Error;
                    ret.m_Position = l_Offset;
                    ret.m_Size = 1;
                    ret.m_Text = tr("} can be found only inside cfscript tag.");
                    break;
                }*/
            }
            else if (ch == ')')
            {
                ret.m_Size = c - p_Offset;
                break;
            }
            else if ((ch == '#')&&(parent)&&(parent->m_Type == SharpExpression))
            {
                ret.m_Size = c - p_Offset;
                break;
            }
            else if (ch == '(')
            {
                child = ParseCFCode(p_Text, c, SubExpression, &ret);
                if (child.m_Type == Error)
                {
                    return child;
                }
                ret.m_ChildElements.append(child);
                c = child.m_Position + child.m_Size;
            }
            else if (ch == '{')
            {
                child = ParseCFCode(p_Text, c, CodeBlock, &ret);
                if (child.m_Type == Error)
                {
                    return child;
                }
                ret.m_ChildElements.append(child);
                ret.m_Size = (child.m_Position + child.m_Size) - ret.m_Position;
                break;
            }
            else if (ch == ';')
            {
                if (m_InsideCFScript)
                {
                    ret.m_Size = c - p_Offset + 1;
                    break;
                }
                else
                {
                    ret.m_Type = Error;
                    ret.m_Position = l_Offset;
                    ret.m_Size = 1;
                    ret.m_Text = tr("; can be found only inside cfscript tag.");
                    break;
                }
            }
            else if (((ch == '/')&&(nextch == '/')&&(m_InsideCFScript))||((ch == '/')&&(nextch == '*')&&(m_InsideCFScript)))
            {
                child = ParseCFCode(p_Text, c, CFComment, &ret);

                if (child.m_Type == Error)
                {
                    return child;
                }

                if (ret.m_ChildElements.count() == 0)
                {
                    return child;
                }
                else
                {
                    ret.m_ChildElements.append(child);
                    c = child.m_Position + child.m_Size;
                }
            }
            else
            {
                if (((ch == '+')||(ch == '-'))&&(ret.m_ChildElements.count() > 0)&&(ret.m_ChildElements.last().m_Type != Operator))
                {
                    child = ParseCFCode(p_Text, c, Operator, &ret);
                }
                else
                {
                    child = ParseCFCode(p_Text, c, Variable, &ret);

                    if ((child.m_Type == Operator)&&(child.m_Text.compare("not", Qt::CaseInsensitive) == 0)&&(ret.m_ChildElements.count() >= 1)) // is not
                    {
                        const QCFParserElement &l_IsElement = ret.m_ChildElements.at(ret.m_ChildElements.count() - 1);

                        if ((l_IsElement.m_Type == Operator)&&(l_IsElement.m_Text.compare("is", Qt::CaseInsensitive) == 0))
                        {
                            ret.m_ChildElements.takeLast();

                            child.m_Type = Operator;
                            child.m_Size = child.m_Position + child.m_Size - l_IsElement.m_Position;
                            child.m_Position = l_IsElement.m_Position;
                            child.m_Text = "is not";
                        }
                    }
                    else if ((child.m_Type == Operator)&&(child.m_Text.compare("equal", Qt::CaseInsensitive) == 0)&&(ret.m_ChildElements.count() >= 1)) // not equal
                    {
                        const QCFParserElement &l_IsElement = ret.m_ChildElements.at(ret.m_ChildElements.count() - 1);

                        if ((l_IsElement.m_Type == Operator)&&(l_IsElement.m_Text.compare("not", Qt::CaseInsensitive) == 0))
                        {
                            ret.m_ChildElements.takeLast();

                            child.m_Type = Operator;
                            child.m_Size = child.m_Position + child.m_Size - l_IsElement.m_Position;
                            child.m_Position = l_IsElement.m_Position;
                            child.m_Text = "not equal";
                        }
                    }
                    else if ((child.m_Type == Variable)&&(child.m_Text.compare("than", Qt::CaseInsensitive) == 0)&&(ret.m_ChildElements.count() >= 1)) // [greater than] and [less than]
                    {
                        const QCFParserElement &l_IsElement = ret.m_ChildElements.at(ret.m_ChildElements.count() - 1);

                        if (l_IsElement.m_Type == Variable)
                        {
                            if (l_IsElement.m_Text.compare("greater", Qt::CaseInsensitive) == 0)
                            {
                                ret.m_ChildElements.takeLast();

                                child.m_Type = Operator;
                                child.m_Size = child.m_Position + child.m_Size - l_IsElement.m_Position;
                                child.m_Position = l_IsElement.m_Position;
                                child.m_Text = "greater than";
                            }
                            else if (l_IsElement.m_Text.compare("less", Qt::CaseInsensitive) == 0)
                            {
                                ret.m_ChildElements.takeLast();

                                child.m_Type = Operator;
                                child.m_Size = child.m_Position + child.m_Size - l_IsElement.m_Position;
                                child.m_Position = l_IsElement.m_Position;
                                child.m_Text = "less than";
                            }
                        }
                    }
                    else if ((child.m_Type == Variable)&&(child.m_Text.compare("contain", Qt::CaseInsensitive) == 0)&&(ret.m_ChildElements.count() >= 2)) // does not contain
                    {
                        const QCFParserElement &l_DoesElement = ret.m_ChildElements.at(ret.m_ChildElements.count() - 2);
                        const QCFParserElement &l_NotElement = ret.m_ChildElements.at(ret.m_ChildElements.count() - 1);

                        if ((l_DoesElement.m_Type == Variable)&&(l_DoesElement.m_Text.compare("does", Qt::CaseInsensitive) == 0)&&(l_NotElement.m_Type == Operator)&&(l_NotElement.m_Text.compare("not", Qt::CaseInsensitive) == 0))
                        {
                            ret.m_ChildElements.takeLast();
                            ret.m_ChildElements.takeLast();

                            child.m_Type = Operator;
                            child.m_Size = child.m_Position + child.m_Size - l_DoesElement.m_Position;
                            child.m_Position = l_DoesElement.m_Position;
                            child.m_Text = "does not contain";
                        }
                    }
                    else if ((child.m_Type == Variable)&&(child.m_Text.compare("to", Qt::CaseInsensitive) == 0)&&(ret.m_ChildElements.count() >= 3)) // [greater than or equal to], and [less than or equal to]
                    {
                        const QCFParserElement &l_CompareElement = ret.m_ChildElements.at(ret.m_ChildElements.count() - 3);
                        const QCFParserElement &l_OrElement = ret.m_ChildElements.at(ret.m_ChildElements.count() - 2);
                        const QCFParserElement &l_EqualElement = ret.m_ChildElements.at(ret.m_ChildElements.count() - 1);

                        if ((l_OrElement.m_Type == Operator)&&(l_OrElement.m_Text.compare("or", Qt::CaseInsensitive) == 0)&&(l_EqualElement.m_Type == Operator)&&(l_EqualElement.m_Text.compare("equal", Qt::CaseInsensitive) == 0)&&(l_CompareElement.m_Type == Operator))
                        {
                            if (l_CompareElement.m_Text.compare("greater than", Qt::CaseInsensitive) == 0)
                            {
                                ret.m_ChildElements.takeLast();
                                ret.m_ChildElements.takeLast();
                                ret.m_ChildElements.takeLast();

                                child.m_Type = Operator;
                                child.m_Size = child.m_Position + child.m_Size - l_CompareElement.m_Position;
                                child.m_Position = l_CompareElement.m_Position;
                                child.m_Text = "greater than or equal to";
                            }
                            else if (l_CompareElement.m_Text.compare("less than", Qt::CaseInsensitive) == 0)
                            {
                                ret.m_ChildElements.takeLast();
                                ret.m_ChildElements.takeLast();
                                ret.m_ChildElements.takeLast();

                                child.m_Type = Operator;
                                child.m_Size = child.m_Position + child.m_Size - l_CompareElement.m_Position;
                                child.m_Position = l_CompareElement.m_Position;
                                child.m_Text = "less than or equal to";
                            }
                        }
                    }
                }
                if (child.m_Type == Error)
                {
                    return child;
                }
                ret.m_ChildElements.append(child);
                c = child.m_Position + child.m_Size;
            }
        }

//            if (ret.m_ChildElements.count() > 0)
//            {
//                ret.m_Size = ret.m_ChildElements.last().m_Position + ret.m_ChildElements.last().m_Size - ret.m_Position;
//            }

        if ((ret.m_ChildElements.count() == 1)&&(ret.m_Position == ret.m_ChildElements.at(0).m_Position)&&(ret.m_Size == ret.m_ChildElements.at(0).m_Size))
        {
            ret = ret.m_ChildElements.at(0);
        }

        break;
    case SubExpression:
        if (p_Text.at(l_Offset) != '(')
        {
            ret.m_Type = Error;
            ret.m_Position = l_Offset;
            ret.m_Text = tr("SubExpression doesn\'t start with '('.");
            break;
        }

        child = ParseCFCode(p_Text, l_Offset + 1, Expression, &ret);
        if (child.m_Type == Error)
        {
            ret = child;
            break;
        }

        if (p_Text.at(l_Offset + child.m_Size + 1) != ')')
        {
            ret.m_Type = Error;
            ret.m_Position = l_Offset;
            ret.m_Text = tr("SubExpression doesn\'t end with ')'.");
            break;
        }

        ret.m_Size = child.m_Size + 2;
        ret.m_ChildElements.append(child);
        break;
    case Function:
        child = ParseCFCode(p_Text, l_Offset, Operator, &ret);
        if (child.m_Type == Operator)
        {
            ret = child;
            break;
        }

        c = p_Text.indexOf('(', l_Offset);

        if (c == -1)
        {
            ret.m_Type = Error;
            ret.m_Text = tr("Can\'t find '(' in function.");
            ret.m_Position = p_Text.length();
            ret.m_Size = 1;
            return ret;
        }



        if (c + 1 >= p_Text.length())
        {
            ret.m_Type = Error;
            ret.m_Text = tr("Unfinished function.");
            ret.m_Position = p_Text.length();
            ret.m_Size = 1;
            return ret;
        }

        child = ParseCFCode(p_Text, c, Parameters, &ret);
        if (child.m_Type == Error)
        {
            return child;
        }

        if (child.m_Size > 2)
        {
            ret.m_ChildElements.append(child);
        }

        ret.m_Text = p_Text.mid(l_Offset, c - l_Offset).trimmed();
        ret.m_Position = l_Offset;
        ret.m_Size = c - l_Offset + child.m_Size;
        break;
    case Parameters:
        c = l_Offset;

        forever
        {
            ch = p_Text.at(c).unicode();

            if (ch == ')')
            {
                ret.m_Size = c - ret.m_Position + 1;
                break;
            }

            c++;

            if (p_Text.length() <= c)
            {
                ret.m_Type = Error;
                ret.m_Position = p_Text.length();
                ret.m_Text = tr("Parametar not finished.");
                return ret;
            }

            child = ParseCFCode(p_Text, c, Parameter, &ret);

            if (child.m_Type == Error)
            {
                ret = child;
                break;
            }

            c = child.m_Position + child.m_Size;

            if (p_Text.length() <= c)
            {
                ret.m_Type = Error;
                ret.m_Position = p_Text.length();
                ret.m_Text = tr("Parametar not finished.");
                return ret;
            }

            ret.m_ChildElements.append(child);
        }

        if (ret.m_ChildElements.count() == 1)
        {
            if (ret.m_ChildElements.at(0).m_Size == 0)
            {
                ret.m_ChildElements.clear();
            }
        }

        break;
    case Parameter:
        child = ParseCFCode(p_Text, l_Offset, Expression, &ret);
        if (child.m_Type == Error)
        {
            return child;
        }
        ret.m_Size = child.m_Size;
        if (child.m_Size == 0)
        {
            break;
        }
        ret.m_ChildElements.append(child);
        break;
    case VariableMember:
        ch = p_Text.at(l_Offset).unicode();
        if ((ch != '.')&&(ch != '['))
        {
            ret.m_Size = 1;
            ret.m_Text = tr("Element not variableMember(Does\'t begin with '.' nor '[').");
            ret.m_Type = Error;
            return ret;
        }

        if (ch == '.')
        {
            ret.m_Text = ".";

            child = ParseCFCode(p_Text, l_Offset + 1, Variable, &ret);
            if (child.m_Type == Error)
            {
                return child;
            }

            ret.m_ChildElements.append(child);
            ret.m_Size = child.m_Size + 1;
        }
        else
        {
            ret.m_Text = "[]";

            child = ParseCFCode(p_Text, l_Offset + 1, Expression, &ret);
            if (child.m_Type == Error)
            {
                return child;
            }

            if (p_Text.at(child.m_Position + child.m_Size) != ']') // TODO: Check for end.
            {
                ret.m_Position = child.m_Position + child.m_Size;
                ret.m_Size = 1;
                ret.m_Text = tr("Element not variableMember(Doesn\'t end with ']').");
                ret.m_Type = Error;
                return ret;
            }

            ret.m_ChildElements.append(child);
            ret.m_Size = child.m_Size + 2;
        }
        break;
    case CFComment:
        ret.m_Size = FindCFCommentSize(p_Text, l_Offset);
        if (ret.m_Size <= 0)
        {
            ret.m_Type = Error;
            ret.m_Text = tr("ColdFusion comment not closed.");
        }
        break;
    case CFScript:

        m_InsideCFScript = true;

        forever
        {
            if (TrimCFCode(p_Text, l_Offset))
            {
                ret.m_Type = Error;
                ret.m_Position = l_Offset - 1;
                ret.m_Text = tr("End of file found.");

                break;
            }

            if (p_Text.mid(l_Offset, 11).compare("</cfscript>", Qt::CaseInsensitive) == 0)
            {
                ret.m_Size = l_Offset - ret.m_Position;

                break;
            }

            child = ParseCFCode(p_Text, l_Offset, Expression, &ret);

            if (child.m_Size == 0)
            {
                child.m_Type = Error;
                child.m_Text = tr("Expression size is 0.");
            }

            ret.m_ChildElements.append(child);

            if (child.m_Type == Error)
            {
                ret.m_Type = Error;
                ret.m_Text = child.m_Text;

                break;
            }

            l_Offset = child.m_Position + child.m_Size;
        }

        m_InsideCFScript = false;

        break;
    default:
        ret.m_Type = Error;
        ret.m_Position = l_Offset;
        ret.m_Text = tr("Not implemented.");
        break;
    }

#ifdef QT_DEBUG
    //if ((ret.m_Position > p_Text.length())||(ret.m_Position < l_Offset))
    if (ret.m_Position > p_Text.length())
    {
        qDebug() << tr("Bad position %1.").arg(ret.m_Position);
    }
#endif

    return ret;
}

QString QCFParser::error()
{
    return m_Error;
}

QString QCFParser::getText() const
{
    return m_Text;
}

quint32 QCFParser::getErrorPosition()
{
    return m_ErrorPosition;
}

quint32 QCFParser::FindCFCommentSize(const QString &p_Text, const quint32 p_Position) /* Done */
{
    quint32 pos = p_Position;

    if (m_InsideCFScript)
    {
        if (p_Text.mid(pos, 2) == "//")
        {
            int cr = p_Text.indexOf("\r", pos + 2, Qt::CaseInsensitive);
            int nl = p_Text.indexOf("\n", pos + 2, Qt::CaseInsensitive);

            if ((cr == -1)&&(nl == -1))
            {
                return p_Text.length() - p_Position;
            }
            else if ((cr == -1)&&(nl > -1))
            {
                return nl - p_Position;
            }
            else if ((cr > -1)&&(nl == -1))
            {
                return cr - p_Position;
            }
            else
            {
                if (nl < cr)
                {
                    return nl - p_Position;
                }
                else
                {
                    return cr - p_Position;
                }
            }
        }
        else if (p_Text.mid(pos, 2) == "/*")
        {
            int endCFComment = p_Text.indexOf("*/", pos + 2, Qt::CaseInsensitive);

            if (endCFComment == -1)
            {
                return p_Text.length() - p_Position;
            }
            else
            {
                return endCFComment - p_Position + 2;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (p_Text.mid(pos, 5) != "<!---")
            return 0;

        pos += 5;

        forever
        {
            int begCFComment, endCFComment, reqPos;

            begCFComment = p_Text.indexOf("<!---", pos, Qt::CaseInsensitive);
            endCFComment = p_Text.indexOf("--->", pos, Qt::CaseInsensitive);

            if ((begCFComment == -1)&&(endCFComment == -1))
                return begCFComment;

            if (endCFComment < begCFComment)
                return endCFComment + 4 - p_Position;

            reqPos = FindCFCommentSize(p_Text, begCFComment);

            if (reqPos == -1)
                return reqPos;

            pos = begCFComment + reqPos;
        }
    }

    return 0;
}

QCFParserErrorType QCFParser::parse(const QFileInfo &p_File, bool *p_Terminate)
{
    QFile file(p_File.filePath());

    if (!p_File.exists())
    {
        m_Error = QObject::tr("File (%1) doesn't exists.").arg(p_File.filePath());

        return ForcedTerminationError;
    }

    m_FileName = p_File.filePath();
    m_FileSize = p_File.size();
    m_FileModifyDateTime = p_File.lastModified().toTime_t();

    if (!file.open(QIODevice::ReadOnly))
    {
        m_Error = QObject::tr("Can't open (%1) file for reading.").arg(p_File.filePath());

        return ForcedTerminationError;
    }

    QString fileContent = QTextStream(&file).readAll();

    if (file.error() != QFileDevice::NoError)
    {
        m_Error = QObject::tr("Error reading source file. Error: %1.").arg(file.errorString());

        return ForcedTerminationError;
    }

    return parse(fileContent, p_Terminate);
}

QCFParserErrorType QCFParser::parse(const QString &p_Text, bool *p_Terminate)
{
    m_Text = p_Text;
    m_Tags.clear();
    m_Error.clear();
    m_ErrorPosition = 0;
    m_InsideCFScript = false;
    m_TagPrefixes.clear();

    int l_CodeInside = 0;
    int pos = 0, cf_pos = 0, cf_epos = 0, cf_comment = 0, cf_expression = 0;

    while(1)
    {
        // For multithread applications. Set p_Terminate to true to stop parsing.
        if ((p_Terminate)&&(*p_Terminate == true))
            return ForcedTerminationError;

        if (cf_pos <= pos)
            cf_pos = p_Text.indexOf("<cf", pos, Qt::CaseInsensitive);
        if (cf_epos <= pos)
            cf_epos = p_Text.indexOf("</cf", pos, Qt::CaseInsensitive);
        if (cf_comment <= pos)
            cf_comment = p_Text.indexOf("<!---", pos, Qt::CaseSensitive);
        if ((l_CodeInside > 0)&&(cf_expression <= pos))
            cf_expression = p_Text.indexOf("#", pos, Qt::CaseSensitive);

        for (const QString &prefix : m_TagPrefixes)
        {
            int tmp_pos;

            tmp_pos = p_Text.indexOf("<" + prefix + ":", pos, Qt::CaseInsensitive);

            if ((tmp_pos >= 0)&&((tmp_pos < (int)cf_pos)||(cf_pos == -1)))
            {
                cf_pos = tmp_pos;
            }

            tmp_pos = p_Text.indexOf("</" + prefix + ":", pos, Qt::CaseInsensitive);

            if ((tmp_pos >= 0)&&((tmp_pos < (int)cf_epos)||(cf_epos == -1)))
            {
                cf_epos = tmp_pos;
            }
        }

        if ((cf_pos == -1) && (cf_epos == -1) && (cf_comment == -1) && ((cf_expression == -1)||(l_CodeInside <= 0)))
            break; // No more ColdFusion tags remaining.

        if ((l_CodeInside > 0)&&(cf_expression < cf_pos)&&(cf_expression < cf_epos)&&(cf_expression < cf_comment))
        {
            QCFParserElement el = ParseCFCode(p_Text, cf_expression, SharpExpression);

            if (el.m_Type == Error)
            {
                this->m_Error = el.m_Text;
                this->m_ErrorPosition = el.m_Position;

                return ParsingError;
            }

            if (el.m_Size > 2)
            {
                QCFParserTag l_codeTag;
                l_codeTag.m_TagType = ExpressionTagType;
                l_codeTag.m_Arguments = el;
                l_codeTag.m_Start = el.m_Position;
                l_codeTag.m_Length = el.m_Size;

                m_Tags.append(l_codeTag);
            }

            pos = el.m_Position + el.m_Size;
            continue;
        }

        if ((cf_pos < cf_epos)&&(cf_pos < cf_comment)) // If <cf tag is the closes one.
        {

            int endName, endNameTemp;

            endName = p_Text.indexOf(' ', cf_pos + 3, Qt::CaseInsensitive);

            endNameTemp = p_Text.indexOf('\r', cf_pos + 3, Qt::CaseInsensitive);
            if (endNameTemp < endName)
                endName = endNameTemp;

            endNameTemp = p_Text.indexOf('\n', cf_pos + 3, Qt::CaseInsensitive);
            if (endNameTemp < endName)
                endName = endNameTemp;

            endNameTemp = p_Text.indexOf('\t', cf_pos + 3, Qt::CaseInsensitive);
            if (endNameTemp < endName)
                endName = endNameTemp;

            endNameTemp = p_Text.indexOf('/', cf_pos + 3, Qt::CaseInsensitive);
            if (endNameTemp < endName)
                endName = endNameTemp;

            endNameTemp = p_Text.indexOf('>', cf_pos + 3, Qt::CaseInsensitive);
            if (endNameTemp < endName)
                endName = endNameTemp;

            endNameTemp = p_Text.indexOf('(', cf_pos + 3, Qt::CaseInsensitive);
            if (endNameTemp < endName)
                endName = endNameTemp;

            if (endName == -1)
            {
                m_Error = tr("ColdFusion tag not closed.");
                m_ErrorPosition = cf_pos;
                return ParsingError;
            }
            QCFParserTag openTag;
            openTag.m_TagType = CFTagType;
            openTag.m_Start = cf_pos;
            //openTag.m_StartLine = linesCount;
            //openTag.m_StartColumn = cf_pos - currentLineIndex;
            openTag.m_Name = p_Text.mid(cf_pos + 1, endName - cf_pos - 1).toLower();
            openTag.m_OtherTag = nullptr;
            if ((m_CFTagsDef.contains(openTag.m_Name))&&(m_CFTagsDef[openTag.m_Name].m_ArgumentsType == QCFTag::ArgumentsTypeExpression))
            {
                openTag.m_Arguments = ParseCFCode(p_Text, endName, CFTagExpression);
            }
            else
            {
                openTag.m_Arguments = ParseCFCode(p_Text, endName, CFTagArguments);
            }

            if (openTag.m_Arguments.m_Type == Error)
            {
                this->m_Error = openTag.m_Arguments.m_Text;
                this->m_ErrorPosition = openTag.m_Arguments.m_Position;

                return ParsingError;
            }

            openTag.m_Length = openTag.m_Arguments.m_Position + openTag.m_Arguments.m_Size - cf_pos;

            int c;
            for(c = 0; openTag.m_Start + openTag.m_Length + c < p_Text.length(); c++)
            {
                if (p_Text.at(openTag.m_Start + openTag.m_Length + c) != ' ')
                {
                    break;
                }
            }

            if (openTag.m_Start + openTag.m_Length + c < p_Text.length())
            {
                if (p_Text[openTag.m_Start + openTag.m_Length + c] == '/')
                {
                    openTag.m_InlineClosedTag = true;
                    openTag.m_Length = openTag.m_Length + c + 2;
                }
                else
                {
                    openTag.m_InlineClosedTag = false;
                    openTag.m_Length = openTag.m_Length + c + 1;
                }
            }
            else
            {
                m_Error = tr("Bad opentag len.");
                m_ErrorPosition = cf_pos;
                return ParsingError;
            }

            if ((openTag.m_Name.left(3).compare("cf_", Qt::CaseInsensitive))&&(openTag.m_Name.left(4).compare("cfx_", Qt::CaseInsensitive))&&(openTag.m_Name.indexOf(':') == -1))
            {
                if (!m_CFTagsDef.contains(openTag.m_Name))
                {
                    m_Error = tr("Unknown cftag '%1'.").arg(openTag.m_Name);
                    m_ErrorPosition = cf_pos;
                    return ParsingError;
                }

                // TODO: Add parameters check.
                if (openTag.m_Arguments.m_Size > 0)
                {
                    if ((m_CFTagsDef[openTag.m_Name].m_ArgumentsType == QCFTag::ArgumentsTypeArguments)&&(openTag.m_Arguments.m_Type != CFTagArguments))
                    {
                        m_Error = tr("Arguments for cftag '%1' must be key/value pair.").arg(openTag.m_Name);
                        m_ErrorPosition = cf_pos;
                        return ParsingError;
                    }

                    if ((m_CFTagsDef[openTag.m_Name].m_ArgumentsType == QCFTag::ArgumentsTypeExpression)&&(openTag.m_Arguments.m_ChildElements.size() > 1))
                    {
                        m_Error = tr("cftag '%1' can't have more than one expression inside.").arg(openTag.m_Name);
                        m_ErrorPosition = cf_pos;
                        return ParsingError;
                    }

                    if ((m_CFTagsDef[openTag.m_Name].m_ArgumentsType == QCFTag::ArgumentsTypeExpression)&&(openTag.m_Arguments.m_ChildElements.size() == 1))
                    {
                        //QCFParserElement temp = openTag.m_Arguments.m_ChildElements[0];
                        //temp.m_Type = Expression;
                        //openTag.m_Arguments = temp;
                        openTag.m_Arguments.m_Type = Expression;
                    }
                }
            }

            if (openTag.m_Name.compare("cfscript", Qt::CaseInsensitive) == 0)
            {
                openTag.m_Arguments = ParseCFCode(p_Text, openTag.m_Start + openTag.m_Length, CFScript);

                if (openTag.m_Arguments.m_Type == Error)
                {
                    m_Error = openTag.m_Arguments.m_Text;
                    m_ErrorPosition = openTag.m_Arguments.m_Position;
                    return ParsingError;
                }

                pos = openTag.m_Arguments.m_Position + openTag.m_Arguments.m_Size;
            }
            else if (openTag.m_Name.compare("cfimport", Qt::CaseInsensitive) == 0)
            {
                for(const QCFParserElement &attribute : openTag.m_Arguments.m_ChildElements)
                {
                    if (attribute.m_ChildElements.count() == 3)
                    {
                        const QCFParserElement &key = attribute.m_ChildElements.at(0);
                        const QCFParserElement &value = attribute.m_ChildElements.at(2);

                        if ((key.m_Type == Variable)&&(key.m_Text.compare("prefix", Qt::CaseInsensitive) == 0)&&(value.m_Type == String))
                        {
                            const QString &item = value.m_Text.trimmed().toLower();

                            if (!m_TagPrefixes.contains(item))
                            {
                                m_TagPrefixes.append(item);

                                break;
                            }
                        }
                    }
                }
            }

            m_Tags.append(openTag);

            if ((openTag.m_Name.left(3).compare("cf_", Qt::CaseInsensitive))&&(openTag.m_Name.left(4).compare("cfx_", Qt::CaseInsensitive))&&(openTag.m_Name.indexOf(':') == -1))
            {
                if (this->m_CFTagsDef.contains(openTag.m_Name))
                {
                    if (this->m_CFTagsDef[openTag.m_Name].m_ExpressionInside == QCFTag::WithExpressionInside)
                    {
                        l_CodeInside++;
                    }
                }
                else
                {
                    m_Error = tr("Unknown cftag '%1'.").arg(openTag.m_Name);
                    m_ErrorPosition = cf_pos;
                    return ParsingError;
                }
            }

            if (openTag.m_Name.compare("cfscript", Qt::CaseInsensitive) != 0)
            {
                pos = openTag.m_Start + openTag.m_Length;
            }
        }
        else if ((cf_epos < cf_pos)&&(cf_epos < cf_comment)) // If </cf tag is the closes one.
        {
            int cf_endtag = p_Text.indexOf('>', cf_epos, Qt::CaseSensitive);
            if (cf_endtag == -1)
            {
                m_Error = tr("Tag not closed. Missing '>'");
                m_ErrorPosition = cf_epos + 1;

                return ParsingError;
            }

            QCFParserTag closeTag;

            closeTag.m_Start = cf_epos;
            closeTag.m_Length = cf_endtag - cf_epos + 1;
            closeTag.m_TagType = EndCFTagType;
            closeTag.m_Name = p_Text.mid(cf_epos + 2, cf_endtag - cf_epos - 2).toLower();
            closeTag.m_Arguments = ParseCFCode(p_Text, cf_endtag, CFTagArguments);
            closeTag.m_InlineClosedTag = false;
            closeTag.m_OtherTag = nullptr;

            m_Tags.append(closeTag);

            if ((closeTag.m_Name.left(3).compare("cf_", Qt::CaseInsensitive))&&(closeTag.m_Name.left(4).compare("cfx_", Qt::CaseInsensitive))&&(closeTag.m_Name.indexOf(':') == -1))
            {
                if (this->m_CFTagsDef.contains(closeTag.m_Name))
                {
                    if (this->m_CFTagsDef[closeTag.m_Name].m_ExpressionInside == QCFTag::WithExpressionInside)
                    {
                        l_CodeInside--;
                    }
                }
                else
                {
                    m_Error = tr("Unknown cftag '%1'.").arg(closeTag.m_Name);
                    m_ErrorPosition = cf_pos;
                    return ParsingError;
                }
            }

            //pos = cf_endtag + 1;
            pos = closeTag.m_Start + closeTag.m_Length;
        }
        else if ((cf_comment < cf_pos)&&(cf_comment < cf_epos)) // If <!--- tag is the closes one.
        {
            QCFParserTag commentTag;

            commentTag.m_Start = cf_comment;
            commentTag.m_Length = FindCFCommentSize(p_Text, cf_comment);
            if (commentTag.m_Length == -1)
            {
                m_Error = tr("The closing tag for the CFML comment is missing. Comment begins on line %1.").arg(GetLineNumberFromPosition(p_Text, cf_comment));
                m_ErrorPosition = p_Text.size();
                return ParsingError;
            }
            commentTag.m_TagType = CommentTagType;
            commentTag.m_Name = p_Text.mid(cf_comment + 5, commentTag.m_Length - 9).trimmed();
            commentTag.m_Arguments = QCFParserElement();
            commentTag.m_Arguments.m_Position = 0;
            commentTag.m_Arguments.m_Size = 0;
            commentTag.m_Arguments.m_Text = "";
            commentTag.m_Arguments.m_Type = Null;
            commentTag.m_InlineClosedTag = false;
            commentTag.m_OtherTag = nullptr;

            m_Tags.append(commentTag);

            //pos = commentTag.m_Start + commentTag.m_Length + 1;
            pos = commentTag.m_Start + commentTag.m_Length;
        }
    }

    QCFParserErrorType l_tagTree = buildTagTree();

    if (l_tagTree != NoError)
    {
        return l_tagTree;
    }

    return validate();
}

QCFParserErrorType QCFParser::buildTagTree()
{
    QList<quint32> nestedList;
    bool Found;

    for (int c = 0; c < m_Tags.size(); c++)
    {
        switch(m_Tags[c].m_TagType)
        {
        case CFTagType:
            if (m_Tags[c].m_InlineClosedTag == false)
                nestedList.append(c);
            break;
        case EndCFTagType:
            Found = false;

            while(nestedList.size() > 0)
            {
                quint32 last = nestedList.takeLast();
                if (m_Tags[c].m_Name == m_Tags[last].m_Name)
                {
                    m_Tags[last].m_OtherTag = &m_Tags[c];
                    m_Tags[c].m_OtherTag = &m_Tags[last];
                    Found = true;
                    break;
                }
            }

            if (Found == false)
            {
                m_Error = tr("Invalid closetag '%1'.").arg(m_Tags[c].m_Name);
                m_ErrorPosition = m_Tags[c].m_Start;
                return InvalidCloseTagError;
            }

            break;
        default:
            break;
        }
    }

    return NoError;
}

void updateElementOffset(QCFParserElement *p_Element, int p_Offset)
{
    if (p_Element)
    {
        p_Element->m_Position += p_Offset;

        for(int c = 0; c < p_Element->m_ChildElements.count(); c++)
        {
            updateElementOffset(&p_Element->m_ChildElements[c], p_Offset);
        }
    }
}

QCFParserErrorType QCFParser::validate()
{
    for (int c = 0; c < m_Tags.size(); c++)
    {
        QCFParserTag &tag = m_Tags[c];

        if (tag.m_TagType != CFTagType)
        {
            continue;
        }

        if ((tag.m_Name.startsWith("cf_"))||(tag.m_Name.startsWith("cfx_"))||(tag.m_Name.indexOf(':') >= 0))
        {
            continue;
        }

        QString l_tagName = tag.m_Name;

        if (!m_CFTagsDef.contains(l_tagName))
        {
#ifdef QT_DEBUG
            qDebug() << l_tagName;
#endif
            m_ErrorPosition = tag.m_Start;
            m_Error = "Invalid tag " + l_tagName + ".";

            return InvalidCFTagError;
        }

        const QCFTag &l_tagDef = m_CFTagsDef[l_tagName];

        if (l_tagDef.m_AnyParam)
        {
            continue;
        }

        if (l_tagDef.m_ArgumentsType != QCFTag::ArgumentsTypeArguments)
        {
            continue;
        }

        if ((l_tagDef.m_ArgumentVariants.count() == 0)&&(tag.m_Arguments.m_ChildElements.count() > 0))
        {
            m_ErrorPosition = tag.m_Start;
            m_Error = l_tagName + " has invalid argument.";

            return InvalidArgumentError;
        }

        if (l_tagDef.m_ArgumentVariants.count() == 0)
        {
            continue;
        }

        for (int c2 = 0; c2 < l_tagDef.m_ArgumentVariants.count(); c2++)
        {
            QList<QCFTagArgument> l_argumentVariant = l_tagDef.m_ArgumentVariants[c2];
            QList<QString> l_requiredArgs;
            bool l_variantFound = true;

            // Get all required parametars
            for(int c3 = 0; c3 < l_argumentVariant.length(); c3++)
            {
                const QCFTagArgument &l_argument = l_argumentVariant[c3];

                if (l_argument.m_Required)
                {
                    l_requiredArgs.append(l_argument.m_Name);
                }
            }

            // check if all of them are present
            for(int c3 = 0; c3 < l_requiredArgs.length(); c3++)
            {
                bool l_requiredArgFound = false;
                for (int c4 = 0; c4 < tag.m_Arguments.m_ChildElements.length(); c4++)
                {
                    if (tag.m_Arguments.m_ChildElements[c4].m_ChildElements[0].m_Text == l_requiredArgs[c3])
                    {
                        l_requiredArgFound = true;
                        break;
                    }
                }

                if (l_requiredArgFound == false)
                {
                    l_variantFound = false;
                    break;
                }
            }

            if (l_variantFound == false)
            {
                continue;
            }

            // check rest of the parametars, generate error if not match here.
            bool l_invalidOptionalArgs = false;
            /*for(int c3 = 0; c3 < l_argumentVariant.length(); c3++)
            {
            	QCFTagArgument l_argument = l_argumentVariant[c3];

            	if (!l_argument.m_Required)
            	{
            		// TODO: Do ovde..
            		if (l_argument.m_Name)
            		{

            		}
            	}
            }*/

            if (l_invalidOptionalArgs)
            {
                return InvalidArgumentError;
            }

            // change parametar value type if nesessary
            for(int c3 = 0; c3 < l_argumentVariant.length(); c3++)
            {
                if (l_argumentVariant[c3].m_Type == QCFTagArgument::TypeExpression)
                {
                    for (int c4 = 0; c4 < tag.m_Arguments.m_ChildElements.count(); c4++)
                    {
                        if (tag.m_Arguments.m_ChildElements[c4].m_ChildElements.length() == 3)
                        {
                            QString argName = tag.m_Arguments.m_ChildElements[c4].m_ChildElements[0].m_Text;

                            if (l_argumentVariant[c3].m_Name == argName)
                            {
                                QString argValue = tag.m_Arguments.m_ChildElements[c4].m_ChildElements[2].m_Text;

                                tag.m_Arguments.m_ChildElements[c4].m_ChildElements[2].m_ChildElements.clear();

                                QCFParserElement el = ParseCFCode(argValue, 0, Expression);

                                updateElementOffset(&el, tag.m_Arguments.m_ChildElements[c4].m_ChildElements[2].m_Position + 1);

                                tag.m_Arguments.m_ChildElements[c4].m_ChildElements[2].m_ChildElements.append(el);
                            }
                        }
                        else
                        {
                            // TODO: Add error.
                        }
                    }
                }
            }
        }
    }

    return NoError;
}

QList<QCFParserTag> QCFParser::getTags() const
{
    return m_Tags;
}

QList<QCFParserElement> QCFParser::getScriptFunctions(QList<QCFParserTag> const p_Tags) const
{
    QList<QCFParserElement> ret;

    for(const QCFParserTag &tag : p_Tags)
    {
        if ((tag.m_Name == "cfscript")&&(tag.m_TagType == CFTagType))
        {
            for(const QCFParserElement &element : tag.m_Arguments.m_ChildElements)
            {
                if ((element.m_Type == Expression)&&(element.m_ChildElements.count() >= 3))
                {
                    if (
                        ((element.m_ChildElements.at(0).m_Type == Keyword)&&(element.m_ChildElements.at(0).m_Text == "function"))||
                        ((element.m_ChildElements.at(1).m_Type == Keyword)&&(element.m_ChildElements.at(1).m_Text == "function"))||
                        ((element.m_ChildElements.at(2).m_Type == Keyword)&&(element.m_ChildElements.at(2).m_Text == "function"))
                    )
                    {
                        ret.append(element);
                    }
                }
            }
        }
    }

    return ret;
}

QList<QCFParserTag> QCFParser::getTagFunctions(QList<QCFParserTag> const p_Tags) const
{
    QList<QCFParserTag> ret;

    for(const QCFParserTag &tag : p_Tags)
    {
        if ((tag.m_Name == "cffunction")&&(tag.m_TagType == CFTagType))
        {
            ret.append(tag);
        }
    }

    return ret;
}

QList<QCFParserTag> QCFParser::getFunctionArguments(const QCFParserTag &p_Function) const
{
    QList<QCFParserTag> ret;
    bool start;


    if (p_Function.m_OtherTag == nullptr)
    {
        return ret;
    }

    start = false;

    for(const QCFParserTag &tag : m_Tags)
    {
        if (start == false)
        {
            if (tag == p_Function)
            {
                start = true;
            }
        }
        else
        {
            if (tag == *p_Function.m_OtherTag)
            {
                break;
            }

            if ((tag.m_TagType == CFTagType)&&(tag.m_Name.compare("cfargument", Qt::CaseInsensitive) == 0))
            {
                ret.append(tag);
            }
        }
    }

    return ret;
}

QCFParserErrorType QCFParser::prioritizeOperatorsRecursive(QCFParserElement &element, const QList<QStringList> &priorities)
{
    if (element.m_ChildElements.count() > 0)
    {
        if (element.m_Type == Expression)
        {
            if (element.m_ChildElements.count() == 1)
            {
                return prioritizeOperatorsRecursive(element.m_ChildElements.first(), priorities);
            }
            else
            {
                for(const QStringList &prority : priorities)
                {
                    for (int c = 0; c < element.m_ChildElements.count(); c++)
                    {
                        const QCFParserElement &item = element.m_ChildElements.at(c);

                        if (((item).m_Type == Operator)&&(prority.contains(item.m_Text.toLower())))
                        {
                            if (item.m_Text.compare("not", Qt::CaseInsensitive) == 0)
                            {
                                if (c >= element.m_ChildElements.count() - 1)
                                {
                                    m_Error = tr("NOT operator can\'t be last.");
                                    m_ErrorPosition = item.m_Position;

                                    return ParsingError;
                                }

                                QCFParserElement newItem;
                                newItem.m_Type = SubExpression;
                                newItem.m_ChildElements.append(element.m_ChildElements.takeAt(c));
                                newItem.m_ChildElements.append(element.m_ChildElements.takeAt(c));
                                newItem.m_Position = newItem.m_ChildElements.first().m_Position;
                                newItem.m_Size = newItem.m_ChildElements.last().m_Position + newItem.m_ChildElements.last().m_Size - newItem.m_ChildElements.first().m_Position;

                                element.m_ChildElements.insert(c, newItem);
                            }
                            else
                            {
                                if (c == 0)
                                {
                                    m_Error = tr("%1 operator can\'t be first.").arg(item.m_Text.toUpper());
                                    m_ErrorPosition = item.m_Position;

                                    return ParsingError;
                                }

                                if (c >= element.m_ChildElements.count() - 1)
                                {
                                    m_Error = tr("%1 operator can\'t be last.").arg(item.m_Text.toUpper());
                                    m_ErrorPosition = item.m_Position;

                                    return ParsingError;
                                }

                                QCFParserElement newItem;
                                newItem.m_Type = SubExpression;
                                newItem.m_ChildElements.append(element.m_ChildElements.takeAt(c - 1));
                                newItem.m_ChildElements.append(element.m_ChildElements.takeAt(c - 1));
                                newItem.m_ChildElements.append(element.m_ChildElements.takeAt(c - 1));
                                newItem.m_Position = newItem.m_ChildElements.first().m_Position;
                                newItem.m_Size = newItem.m_ChildElements.last().m_Position + newItem.m_ChildElements.last().m_Size - newItem.m_ChildElements.first().m_Position;

                                element.m_ChildElements.insert(c - 1, newItem);
                                c--;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            for (QCFParserElement child : element.m_ChildElements)
            {
                prioritizeOperatorsRecursive(child, priorities);
            }
        }
    }

    return NoError;
}

quint32 QCFParser::GetLineNumberFromPosition(const QString &p_FileContent, int p_FileOffset)
{
    quint32 ret = 1;

    for(int offset = p_FileContent.indexOf('\n', 0, Qt::CaseInsensitive); offset != -1; offset = p_FileContent.indexOf('\n', offset + 1, Qt::CaseInsensitive))
    {
        if (offset > p_FileOffset)
        {
            break;
        }

        ret++;
    }

    return ret;
}

quint32 QCFParser::GetColumnNumberFromPosition(const QString &p_FileContent, int p_FileOffset)
{
    int offset = 0;

    for(offset = p_FileContent.indexOf('\n', 0, Qt::CaseInsensitive); offset != -1; offset = p_FileContent.indexOf('\n', offset + 1, Qt::CaseInsensitive))
    {
        if (offset > p_FileOffset)
        {
            break;
        }
    }

    return p_FileOffset - offset + 1;
}

QCFParserErrorType QCFParser::prioritizeOperators()
{
    QList<QStringList> l_ExceptionPriorities;

    l_ExceptionPriorities.append(QStringList() << "^");
    l_ExceptionPriorities.append(QStringList() << "*"); // for incrased precision move multiply before divide
    l_ExceptionPriorities.append(QStringList() << "/" << "\\" << "mod");
    l_ExceptionPriorities.append(QStringList() << "+" << "-");
    l_ExceptionPriorities.append(QStringList() << "&");
    l_ExceptionPriorities.append(QStringList() << "is" << "eq" << "equal" << "is not" << "neq" << "not equal"
                                 << "greater than" << "gt" << "less than" << "lt" << "greater than or equal to"
                                 << "gte" << "ge" << "less than or equal to" << "lte" << "le" << "contains"
                                 << "does not contain");
    l_ExceptionPriorities.append(QStringList() << "not");

    for(QCFParserTag &tag : m_Tags)
    {
        if (tag.m_TagType == CFTagType)
        {
            QCFParserErrorType err =  prioritizeOperatorsRecursive(tag.m_Arguments, l_ExceptionPriorities);

            if (err != NoError)
            {
                return err;
            }
        }
    }

    return NoError;
}
