#include "qcfgenerator.h"
#include "qcfgeneratorexception.h"
#include "qcfcomponentgenerator.h"
#include "qcfparser.h"

#include <QRegularExpressionMatch>
#include <QRegularExpression>
#include <QTextStream>
#include <QDateTime>
#include <QFileInfo>
#include <QProcess>
#include <QList>
#include <QFile>
#include <QDir>


QCFGenerator::QCFGenerator()
    : m_Parser(CompilerMode, QCFParserTemplateFile)
    , m_EnableCFOutputOnly(false)
    , m_InsideCFQueryTag(false)
    , m_Tabs(2)
{
}

QCFGenerator::~QCFGenerator()
{
}

bool QCFGenerator::generate(const QString &srcFilePath, const QString &dstFilePath)
{
    if (m_Parser.parse(QFileInfo(srcFilePath)) != NoError)
    {
        m_Error = QObject::tr("Parser error: %1.").arg(m_Parser.error());

        return false;
    }

    if (m_Parser.prioritizeOperators() != NoError)
    {
        m_Error = QObject::tr("Parser error(prioritize operators): %1.").arg(m_Parser.error());

        return false;
    }

    if (m_Parser.buildTagTree() != NoError)
    {
        m_Error = QObject::tr("Parser error(build tag tree): %1.").arg(m_Parser.error());

        return false;
    }

    try
    {
        generateCpp(dstFilePath);
    }
    catch(const QCFGeneratorException &ex)
    {
        int line = 0;
        int col = 0;
        m_Error = QObject::tr("Generator error: (%1), at line: %2:%3.").arg(ex.m_Message).arg(line).arg(col);

        return false;
    }

    return true;
}

QString QCFGenerator::error() const
{
    return m_Error;
}

QByteArray QCFGenerator::toCPPEncodedString(const QString &string)
{
    QByteArray ret;

    for(const QChar &qch : string)
    {
        ushort ch = qch.unicode();

        switch(ch)
        {
        case '\0':
            ret.append("\\0");
            continue;
            break;
        case '\\':
            ret.append("\\\\");
            continue;
            break;
        case '\'':
            ret.append("\\\'");
            continue;
            break;
        case '\"':
            ret.append("\\\"");
            continue;
            break;
        case '\n':
            ret.append("\\n");
            continue;
            break;
        case '\r':
            ret.append("\\r");
            continue;
            break;
        case '\t':
            ret.append("\\t");
            continue;
            break;
        }

        if ((ch >= 32)&&(ch <= 128))
        {
            ret.append((char)ch);
            continue;
        }

        QByteArray tmp = QByteArray::number(ch, 16);

        while(tmp.length() < 4)
        {
            tmp.prepend('0');
        }

        tmp.prepend("\\x");

        ret.append(tmp);
    }

    return ret;
}

QString QCFGenerator::GenerateVariable(const QString &p_Variable, const QString &p_Funct_params, const QString &p_Funct_local_vars, bool assignment)
{
    QString ret;
    QString l_Variable = p_Variable.toUpper();

    QStringList functParams = p_Funct_params.split(",");
    QStringList functLocalVars = p_Funct_local_vars.split(",");

    if (
        (!l_Variable.startsWith("CGI.")) \
        && (l_Variable.compare("CGI") != 0) \
        && (!l_Variable.startsWith("SERVER.")) \
        && (l_Variable.compare("SERVER") != 0) \
        && (!l_Variable.startsWith("APPLICATION.")) \
        && (l_Variable.compare("APPLICATION") != 0) \
        && (!l_Variable.startsWith("SESSION.")) \
        && (l_Variable.compare("SESSION") != 0) \
        && (!l_Variable.startsWith("COOKIE.")) \
        && (l_Variable.compare("COOKIE") != 0) \
        && (!l_Variable.startsWith("URL.")) \
        && (l_Variable.compare("URL") != 0) \
        && (!l_Variable.startsWith("FORM.")) \
        && (l_Variable.compare("FORM") != 0) \
        && (!l_Variable.startsWith("VARIABLES.")) \
        && (l_Variable.compare("VARIABLES") != 0) \
    )
    {
        if ((functLocalVars.contains(l_Variable))&&(!l_Variable.startsWith("LOCAL."))&&(l_Variable.compare("LOCAL") != 0))
        {
            l_Variable = "LOCAL." + l_Variable;
        }
        else if ((functParams.contains(l_Variable))&&(!l_Variable.startsWith("ARGUMENTS."))&&(l_Variable.compare("ARGUMENTS") != 0))
        {
            l_Variable = "ARGUMENTS." + l_Variable;
        }
        else
        {
            l_Variable = "VARIABLES." + l_Variable;
        }
    }

    QStringList l_StrList = l_Variable.split(".");

    if (l_StrList.size() < 1)
    {
        return "";
    }

    if ((l_StrList.first() == "LOCAL")||(l_StrList.first() == "ARGUMENTS"))
    {
        ret = l_StrList.first();
    }
    else
    {
        if ((l_StrList.first() == "SESSION")|(l_StrList.first() == "APPLICATION"))
        {
            ret = "(*m_" + l_StrList.first() + ")";
        }
        else
        {
            ret = "m_" + l_StrList.first();
        }
    }

    for(int c = 1; c < l_StrList.size(); c++)
    {
        if (assignment)
        {
            ret += "._()";
        }

        ret += "[L\"" + l_StrList[c] + "\"]";
    }

    return ret;
}

QString QCFGenerator::GenerateCFExpressionToCExpression(const QCFParserElement &p_CFExpression, const QString &funct_params, QString &funct_local_vars, bool assignment)
{
    QString l_ElementName, l_worker;
    QStringList strList;
    QString ret;
    int c;

    const QHash<QString, QCFFunction> &l_CFFunctionsDef = m_Parser.m_CFFunctionsDef;

    if (isComponent())
    {
        l_worker = "worker.";
    }

    l_ElementName = p_CFExpression.m_Text;

    switch(p_CFExpression.m_Type)
    {
    case Boolean:
        l_ElementName = l_ElementName.toLower().trimmed();

        if ((l_ElementName == "true")||(l_ElementName == "yes"))
        {
            ret = "true";
        }
        else if ((l_ElementName == "false")||(l_ElementName == "no"))
        {
            ret = "false";
        }
        else
        {
            throw QCFGeneratorException("Invalid boolean value.", p_CFExpression.m_Position);
        }
        break;
    case Number:
        ret = l_ElementName;
        break;
    case String:
        if (p_CFExpression.m_ChildElements.size() == 1)
        {
            ret = GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements.first(), funct_params, funct_local_vars, assignment);
        }
        else if (p_CFExpression.m_ChildElements.size() > 0)
        {
            ret += '(';

            for(c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
            {
                if (c == 0)
                {
                    ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars, assignment);
                }
                else
                {
                    if (p_CFExpression.m_Type == String)
                    {
                        ret += " & " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars, assignment);
                    }
                    else
                    {
                        ret += " + " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars, assignment);
                    }
                }
            }

            ret += ')';
        }
        else
        {
            ret = "QString::fromWCharArray(L\"" + toCPPEncodedString(l_ElementName) + "\")";
        }
        break;
    case Variable:
        ret = GenerateVariable(l_ElementName, funct_params, funct_local_vars, assignment);

        for (c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
        {
            ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars, assignment);
        }
        break;
    case VariableMember:
        if (p_CFExpression.m_ChildElements.count() == 1)
        {
            const QCFParserElement &item = p_CFExpression.m_ChildElements.first();

            if (item.m_Type == Variable)
            {
                if (assignment)
                {
                    ret = "._()";
                }

                ret += "[L\"" + item.m_Text.toUpper() + "\"]";
            }
            else if (item.m_Type == String)
            {
                if (assignment)
                {
                    ret = "._()";
                }

                ret += "[L\"" + item.m_Text + "\"]";
            }
            else if (item.m_Type == Number)
            {
                ret = "[" + item.m_Text + "]";
            }
            else if (item.m_Type == Function)
            {
                ret = "." + GenerateCFExpressionToCExpression(item, funct_params, funct_local_vars, assignment);
            }
            else
            {
                throw QCFGeneratorException("Unknown member access.", item.m_Position);
            }
        }
        else if (p_CFExpression.m_ChildElements.count() > 1)
        {
            ret = "[" + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[0], funct_params, funct_local_vars, assignment) + "]";
        }
        else
        {
            throw QCFGeneratorException("Unknown member access.", p_CFExpression.m_Position);
        }
        break;
    case Function:
        if (l_CFFunctionsDef.contains(l_ElementName.toLower()))
        {
            if (l_CFFunctionsDef[l_ElementName.toLower()].m_NeedsThis)
            {
                ret = "cf_" + l_CFFunctionsDef[l_ElementName.toLower()].m_Name + "(this";

                if (l_CFFunctionsDef[l_ElementName.toLower()].m_Arguments.count() > 0)
                {
                    ret += ", ";
                }
            }
            else
            {
                ret = "cf_" + l_CFFunctionsDef[l_ElementName.toLower()].m_Name + "(";
            }

            for (c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
            {
                if (c > 0)
                {
                    ret += ", ";
                }
                ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars, assignment);
            }
        }
        else
        {
            if (m_Parser.m_FileType == QCFParserTemplateFile)
            {
                ret = "call(*this, QString::fromWCharArray(L\"" + toCPPEncodedString(l_ElementName.toLower()) + "\"), QList<QCFVariant>()";
            }
            else
            {
                ret = "call(worker, QString::fromWCharArray(L\"" + toCPPEncodedString(l_ElementName.toLower()) + "\"), QList<QCFVariant>()";
            }

            if (p_CFExpression.m_ChildElements.count() > 0)
            {
                if (p_CFExpression.m_ChildElements.count() == 1)
                {
                    const QCFParserElement &parameters = p_CFExpression.m_ChildElements.at(0);

                    if (parameters.m_Type == Parameters)
                    {
                        for (c = 0; c < parameters.m_ChildElements.size(); c++)
                        {
                            ret += " << (" + GenerateCFExpressionToCExpression(parameters.m_ChildElements[c], funct_params, funct_local_vars, assignment) + ")";
                        }
                    }
                    else
                    {
                        throw QCFGeneratorException("Tag function has children type other than parameters.", p_CFExpression.m_Position);
                    }
                }
                else
                {
                    throw QCFGeneratorException("Tag function has more than one children.", p_CFExpression.m_Position);
                }
            }
        }

        ret += ")";
        break;
    case Operator:
        if ((l_ElementName.compare(l_ElementName, "eq", Qt::CaseInsensitive) == 0)
                ||(l_ElementName.compare(l_ElementName, "is", Qt::CaseInsensitive) == 0))
        {
            ret = " == ";
        }
        else if (l_ElementName.compare(l_ElementName, "gt", Qt::CaseInsensitive) == 0)
        {
            ret = " > ";
        }
        else if (l_ElementName.compare(l_ElementName, "gte", Qt::CaseInsensitive) == 0)
        {
            ret = " >= ";
        }
        else if (l_ElementName.compare(l_ElementName, "lt", Qt::CaseInsensitive) == 0)
        {
            ret = " < ";
        }
        else if (l_ElementName.compare(l_ElementName, "lte", Qt::CaseInsensitive) == 0)
        {
            ret = " <= ";
        }
        else if (l_ElementName.compare(l_ElementName, "neq", Qt::CaseInsensitive) == 0)
        {
            ret = " != ";
        }
        else if (l_ElementName.compare(l_ElementName, "and", Qt::CaseInsensitive) == 0)
        {
            ret = " && ";
        }
        else if (l_ElementName.compare(l_ElementName, "or", Qt::CaseInsensitive) == 0)
        {
            ret = " || ";
        }
        else if (l_ElementName.compare(l_ElementName, "not", Qt::CaseInsensitive) == 0)
        {
            ret = " !";
        }
        else if (l_ElementName == "(")
        {
            ret = "(";
        }
        else if (l_ElementName == ")")
        {
            ret = ")";
        }
        else if (l_ElementName == "[")
        {
            ret = "]";
        }
        else if (l_ElementName == "]")
        {
            ret = "]";
        }
        else if (l_ElementName.compare("mod", Qt::CaseInsensitive) == 0)
        {
            ret = " % ";
        }
        else
        {
            ret = " " + l_ElementName + " ";
        }
        break;
    case Parameter:
        for (c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
        {
            ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars, assignment);
        }
        break;
    case Parameters:
        for (c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
        {
            if (c == 0)
            {
                ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars, assignment);
            }
            else
            {
                ret += ", " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars, assignment);
            }
        }
        break;
    case SharpExpression:
        ret = GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[0], funct_params, funct_local_vars, assignment);
        break;
    case Expression:
        c = 0;

        if (p_CFExpression.m_ChildElements.size() >= 2)
        {
            const QCFParserElement &var = p_CFExpression.m_ChildElements.at(0);
            const QCFParserElement &variable = p_CFExpression.m_ChildElements.at(1);

            if ((var.m_Type == Keyword)&&(var.m_Text.compare("var", Qt::CaseInsensitive) == 0)&&(variable.m_Type == Variable))
            {
                if (funct_local_vars.isEmpty())
                {
                    funct_local_vars = variable.m_Text.toUpper();
                }
                else
                {
                    funct_local_vars += "," + variable.m_Text.toUpper();
                }
            }
        }

        if (p_CFExpression.m_ChildElements.size() >= 3)
        {
            const QCFParserElement &op1 = p_CFExpression.m_ChildElements.at(1);

            if ((op1.m_Type == Operator)&&(op1.m_Text == "="))
            {
                const QCFParserElement &destVar = p_CFExpression.m_ChildElements.at(0);

                if ((destVar.m_Type == Variable)&&(destVar.m_ChildElements.count() == 0))
                {
                    QStringList localVars;
                    if(!funct_local_vars.isEmpty())
                    {
                        localVars = funct_local_vars.split(',');
                    }

                    if (localVars.contains(destVar.m_Text.toUpper()))
                    {
                        ret += l_worker + "LOCAL._()[L\"" + toCPPEncodedString(destVar.m_Text.toUpper()) + "\"] = ";
                    }
                    else
                    {
                        ret += l_worker + "m_VARIABLES._()[L\"" + toCPPEncodedString(destVar.m_Text.toUpper()) + "\"] = ";
                    }
                }
                else if(destVar.m_ChildElements.count() > 0)
                {
                    ret += l_worker + GenerateCFExpressionToCExpression(destVar, funct_params, funct_local_vars, true) + " = ";
                }
                else
                {
                    return "";
                }

                c = 2;
            }
            else
            {
                // ex: var a = 12
                const QCFParserElement &op2 = p_CFExpression.m_ChildElements.at(2);

                if ((op2.m_Type == Operator)&&(op2.m_Text == "=")&&(p_CFExpression.m_ChildElements.first().m_Type == Keyword)&&(p_CFExpression.m_ChildElements.first().m_Text == "var"))
                {
                    const QCFParserElement &destVar = p_CFExpression.m_ChildElements.at(1);

                    if ((destVar.m_Type == Variable)&&(destVar.m_ChildElements.count() == 0))
                    {
                        ret += l_worker + "LOCAL._()[\"" + toCPPEncodedString(destVar.m_Text.toUpper()) + "\"] = ";
                    }
                    else if(destVar.m_ChildElements.count() > 0)
                    {
                        ret += l_worker + GenerateCFExpressionToCExpression(destVar, funct_params, funct_local_vars, true);
                    }
                    else
                    {
                        return "";
                    }

                    c = 3;
                }
            }
        }

        for (; c < p_CFExpression.m_ChildElements.size(); c++)
        {
            ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars, assignment);
        }

        break;
    case SubExpression:

        for (const QCFParserElement &expr : p_CFExpression.m_ChildElements)
        {
            strList << GenerateCFExpressionToCExpression(expr, funct_params, funct_local_vars, assignment);
        }

        ret.append("(" + strList.join(" ") + ")");
        break;

    case CodeBlock:

        ret += tabs() + " {\n";

        m_Tabs++;

        for (const QCFParserElement &expr : p_CFExpression.m_ChildElements)
        {
            ret += tabs() + GenerateCFExpressionToCExpression(expr, funct_params, funct_local_vars, assignment) + " ";

            if ((expr.m_Type == Expression)&&(expr.m_ChildElements.count() > 0))
            {
                if (expr.m_ChildElements.last().m_Type != CodeBlock)
                {
                    ret += ";";
                }
            }

            ret += "\n";
        }

        m_Tabs--;

        ret += tabs() + "}\n";
        break;

    case Keyword:

        if (p_CFExpression.m_Text.compare("this", Qt::CaseInsensitive) == 0)
        {
            ret += "self";
        }
        else if (p_CFExpression.m_Text.compare("var", Qt::CaseInsensitive) != 0)
        {
            ret += p_CFExpression.m_Text + " ";
        }

        break;
    default:
        break;
    }

    return ret;
}

QCFParserElement QCFGenerator::OptimizeQCFParserElement(QCFParserElement p_CFExpression)
{
    for(int c = 0; c < p_CFExpression.m_ChildElements.count(); c++)
    {
        p_CFExpression.m_ChildElements[c] = OptimizeQCFParserElement(p_CFExpression.m_ChildElements[c]);
    }

    if ((p_CFExpression.m_ChildElements.length() == 1)&&((p_CFExpression.m_Type == Expression)||(p_CFExpression.m_Type == SharpExpression)||(p_CFExpression.m_Type == Parameters)||(p_CFExpression.m_Type == Parameter)))// TODO: Maybe add another types
    {
        return p_CFExpression.m_ChildElements[0];
    }

    return p_CFExpression;
}

QString QCFGenerator::ParseAndGenerateCppExpressionFromString(const QString str)
{
    QCFParser parser(CompilerMode, m_Parser.m_FileType);
    QString local_vars;

    QCFParserElement l_newConditionElement = parser.ParseCFCode(str, (qint32)0, Expression, nullptr);

    return GenerateCFExpressionToCExpression(OptimizeQCFParserElement(l_newConditionElement), "", local_vars);
}

bool CFTagHasArgument(const QCFParserTag &p_CFTag, const QString &p_Argument)
{
    for(const QCFParserElement &l_Argument: p_CFTag.m_Arguments.m_ChildElements)
    {
        if ((l_Argument.m_Type != CFTagArgument)||(l_Argument.m_ChildElements.size() < 1))
        {
            continue;
        }

        if (l_Argument.m_ChildElements[0].m_Text.compare(p_Argument, Qt::CaseInsensitive) == 0)
        {
            return true;
        }
    }

    return false;
}

QCFParserElement CFTagGetArgumentObject(const QCFParserTag &p_CFTag, const QString &p_Argument)
{
    for(const QCFParserElement &l_Argument: p_CFTag.m_Arguments.m_ChildElements)
    {
        if ((l_Argument.m_Type != CFTagArgument)||(l_Argument.m_ChildElements.size() < 1))
        {
            continue;
        }

        if (l_Argument.m_ChildElements[0].m_Text.compare(p_Argument, Qt::CaseInsensitive) == 0)
        {
            return l_Argument;
        }
    }

    QCFParserElement ret;
    ret.m_Type = Error;

    return ret;
}

QString QCFGenerator::CFTagGetArgumentPlain(const QCFParserTag &p_CFTag, const QString &p_Argument)
{
    for(const QCFParserElement &l_Argument: p_CFTag.m_Arguments.m_ChildElements)
    {
        if ((l_Argument.m_Type != CFTagArgument)||(l_Argument.m_ChildElements.size() < 1))
        {
            continue;
        }

        if (l_Argument.m_ChildElements[0].m_Text.compare(p_Argument, Qt::CaseInsensitive) == 0)
        {
            if (l_Argument.m_ChildElements.size() == 3)
            {
                return l_Argument.m_ChildElements.at(2).m_Text;
            }
        }
    }

    return "";
}

QString QCFGenerator::CFTagGetArgument(const QCFParserTag &p_CFTag, const QString &p_Argument)
{
    for(const QCFParserElement &l_Argument: p_CFTag.m_Arguments.m_ChildElements)
    {
        if ((l_Argument.m_Type != CFTagArgument)||(l_Argument.m_ChildElements.size() < 1))
        {
            continue;
        }

        if (l_Argument.m_ChildElements[0].m_Text.compare(p_Argument, Qt::CaseInsensitive) == 0)
        {
            if (l_Argument.m_ChildElements.size() == 3)
            {
                QString local_vars;

                return GenerateCFExpressionToCExpression(l_Argument.m_ChildElements.at(2), "", local_vars);
            }
        }
    }

    return "";
}

QString QCFGenerator::CFTagGetArgumentAsString(const QCFParserTag &p_CFTag, const QString &p_Argument)
{
    for(const QCFParserElement &l_Argument: p_CFTag.m_Arguments.m_ChildElements)
    {
        if ((l_Argument.m_Type != CFTagArgument)||(l_Argument.m_ChildElements.size() < 1))
        {
            continue;
        }

        if (l_Argument.m_ChildElements[0].m_Text.compare(p_Argument, Qt::CaseInsensitive) == 0)
        {
            if (l_Argument.m_ChildElements.size() == 3)
            {
                if (l_Argument.m_ChildElements.at(2).m_Type == String)
                {
                    QString local_vars;

                    return GenerateCFExpressionToCExpression(l_Argument.m_ChildElements.at(2), "", local_vars);
                }
            }

            break;
        }
    }

    throw QCFGeneratorException("Value is not string.", p_CFTag.m_Start);
}

QString QCFGenerator::CFTagGetArgumentAsNumber(const QCFParserTag &p_CFTag, const QString &p_Argument)
{
    for(const QCFParserElement &l_Argument: p_CFTag.m_Arguments.m_ChildElements)
    {
        if ((l_Argument.m_Type != CFTagArgument)||(l_Argument.m_ChildElements.size() < 1))
        {
            continue;
        }

        if (l_Argument.m_ChildElements[0].m_Text.compare(p_Argument, Qt::CaseInsensitive) == 0)
        {
            if (l_Argument.m_ChildElements.size() == 3)
            {
                if (l_Argument.m_ChildElements.at(2).m_Type == Number)
                {
                    return l_Argument.m_ChildElements.at(2).m_Text;
                }
                else if (l_Argument.m_ChildElements.at(2).m_Type == String)
                {
                    bool ok;

                    l_Argument.m_ChildElements.at(2).m_Text.trimmed().toFloat(&ok);

                    if (ok)
                    {
                        return l_Argument.m_ChildElements.at(2).m_Text;
                    }

                    QString local_vars;

                    return GenerateCFExpressionToCExpression(l_Argument.m_ChildElements.at(2), "", local_vars);

                }
                else
                {
                    QString local_vars;

                    return GenerateCFExpressionToCExpression(l_Argument.m_ChildElements.at(2), "", local_vars);
                }
            }

            break;
        }
    }

    throw QCFGeneratorException("Value is not number.", p_CFTag.m_Start);
}

QString QCFGenerator::CFTagGetArgumentAsBool(const QCFParserTag &p_CFTag, const QString &p_Argument)
{
    for(const QCFParserElement &l_Argument: p_CFTag.m_Arguments.m_ChildElements)
    {
        if ((l_Argument.m_Type != CFTagArgument)||(l_Argument.m_ChildElements.size() < 1))
        {
            continue;
        }

        if (l_Argument.m_ChildElements[0].m_Text.compare(p_Argument, Qt::CaseInsensitive) == 0)
        {
            if (l_Argument.m_ChildElements.size() == 3)
            {
                if (l_Argument.m_ChildElements.at(2).m_Type == String)
                {
                    const QString value = l_Argument.m_ChildElements.at(2).m_Text.trimmed();

                    if ((value.compare("true", Qt::CaseInsensitive) == 0)||(value.compare("yes", Qt::CaseInsensitive) == 0))
                    {
                        return "true";
                    }
                    if ((value.compare("false", Qt::CaseInsensitive) == 0)||(value.compare("no", Qt::CaseInsensitive) == 0))
                    {
                        return "false";
                    }
                }
            }

            break;
        }
    }

    throw QCFGeneratorException("Value is not boolean.", p_CFTag.m_Start);
}

QString QCFGenerator::GenerateCCodeFromCFTag(const QCFParserTag &p_CFTag)
{
    QString l_worker;

    if (isComponent())
    {
        l_worker = "worker.";
    }

    if (p_CFTag.m_TagType == ExpressionTagType)
    {
        QString local_vars;

        return tabs() + "f_WriteOutput(" + GenerateCFExpressionToCExpression(p_CFTag.m_Arguments, "", local_vars) + ");";
    }

    if (p_CFTag.m_OtherTag)
    {
        if (p_CFTag.m_TagType == CFTagType)
        {
            m_NestedTags.append(&p_CFTag);
        }
        else
        {
            m_NestedTags.takeLast();
        }
    }

    if ((p_CFTag.m_TagType != CFTagType)&&(p_CFTag.m_TagType != EndCFTagType))
    {
        return "";
    }

    if(p_CFTag.m_Name.compare("cfabort", Qt::CaseInsensitive) == 0) // Done
    {
        if (CFTagHasArgument(p_CFTag, "showError"))
        {
            return tabs() + "throw QMKFusionExpressionException(" + CFTagGetArgumentPlain(p_CFTag, "showError") + ");";
        }
        else
        {
            return tabs() + "throw QMKFusionCFAbortException();";
        }
    }
    else if(p_CFTag.m_Name.compare("cfassociate", Qt::CaseInsensitive) == 0) // Done
    {
        if (p_CFTag.m_TagType == CFTagType)
        {
            QString baseTag;
            QString dataCollection;

            if(!CFTagHasArgument(p_CFTag, "baseTag"))
            {
                throw QCFGeneratorException("cfassociate tag needs baseTag attributes.", p_CFTag.m_Start);
            }

            baseTag = CFTagGetArgumentAsString(p_CFTag, "baseTag");
            if(CFTagHasArgument(p_CFTag, "dataCollection"))
            {
                dataCollection = CFTagGetArgumentAsString(p_CFTag, "dataCollection");
            }
            else
            {
                dataCollection = "\"" + toCPPEncodedString("AssocAttrib") + "\"";
            }

            return tabs() + "f_cfAssociate(" + baseTag + ", " + dataCollection + ");\n";
        }
    }
    else if(p_CFTag.m_Name.compare("cfapplication", Qt::CaseInsensitive) == 0) // TODO: cfapplication - Implemented attributes: name, sessionmanagement, setclientcookies
    {
        bool has_name = CFTagHasArgument(p_CFTag, "name");

        if (has_name)
        {
            return tabs() + "f_Application(" + CFTagGetArgumentAsString(p_CFTag, "name") + ", " + CFTagGetArgumentAsBool(p_CFTag, "sessionmanagement") + ", " + CFTagGetArgumentAsBool(p_CFTag, "setclientcookies") + ");";
        }
        else
        {
            throw QCFGeneratorException("cfapplication tag must have name attribute.", p_CFTag.m_Start);
        }
    }
    else if(p_CFTag.m_Name.compare("cfbreak", Qt::CaseInsensitive) == 0) // Done
    {
        return tabs() + "break;";
    }
    else if(p_CFTag.m_Name.compare("cfcase", Qt::CaseInsensitive) == 0) // TODO: cfcase - Unimplemented attribute: delimiters
    {
        QString ret;

        if (p_CFTag.m_TagType == CFTagType)
        {
            if(m_SwitchCaseCount.last() > 0)
            {
                ret = tabs() + "else ";
            }

            m_SwitchCaseCount[m_SwitchCaseCount.count() - 1]++;

            QString switchValue = CFTagGetArgument(*m_SwitchTags.last(), "expression");
            QString caseValue = CFTagGetArgument(p_CFTag, "value");

            if (ret.isEmpty())
            {
                ret = tabs() + "if (" + switchValue + " == " + caseValue + ")\n";
            }
            else
            {
                ret += "if (" + switchValue + " == " + caseValue + ")\n";
            }

            ret += tabs() + "{\n";

            m_Tabs++;

            return ret;
        }
        else if (p_CFTag.m_TagType == EndCFTagType)
        {
            m_Tabs--;

            return tabs() + "}\n";
        }
    }
    else if(p_CFTag.m_Name.compare("cfcatch", Qt::CaseInsensitive) == 0) // TODO: cfcatch - attribute: "type", value: "custom_type" are not implemented
    {
        // TODO: NOT all cfcatch types are implemented.
        if (p_CFTag.m_TagType == CFTagType)
        {
            if (CFTagHasArgument(p_CFTag, "type"))
            {
                const QString &type = CFTagGetArgumentAsString(p_CFTag, "type").toLower();

                if (type == "application")
                {
                    return tabs(-1) + "} catch(const QMKFusionApplicationException &ex) {";
                }
                else if(type == "database")
                {
                    return tabs(-1) + "} catch(const QMKFusionDatabaseException &ex) {";
                }
                else if(type == "security")
                {
                    return tabs(-1) + "} catch(const QMKFusionSecurityException &ex) {";
                }
                else if(type == "object")
                {
                    return tabs(-1) + "} catch(const QMKFusionObjectException &ex) {";
                }
                else if(type == "missinginclude")
                {
                    return tabs(-1) + "} catch(const QMKFusionMissingIncludeException &ex) {";
                }
                else if(type == "template")
                {
                    return tabs(-1) + "} catch(const QMKFusionTemplateException &ex) {";
                }
                else if(type == "expression")
                {
                    return tabs(-1) + "} catch(const QMKFusionExpressionException &ex) {";
                }
                else if(type == "lock")
                {
                    return tabs(-1) + "} catch(const QMKFusionLockException &ex) {";
                }
                else if(type == "searchengine")
                {
                    return tabs(-1) + "} catch(const QMKFusionSearchEngineException &ex) {";
                }
                else if(type == "any")
                {
                    return tabs(-1) + "} catch(const QMKFusionException &ex) {";
                }
                else
                {
                    throw QCFGeneratorException(QString("Invalid cfcatch type[%1]").arg(type), p_CFTag.m_Start);
                }
            }

            return tabs(-1) + "} catch(const QMKFusionException &ex) {";
        }
    }
    else if(p_CFTag.m_Name.compare("cfcookie", Qt::CaseInsensitive) == 0) // TODO: cfcookie - Unimplemented attribute: domain, path, secure
    {
        QString name = CFTagGetArgumentAsString(p_CFTag, "name");
        QString value;
        QString expires;

        if (CFTagHasArgument(p_CFTag, "value"))
        {
            value = CFTagGetArgumentAsString(p_CFTag, "value");
        }
        else
        {
            value = "\"\"";
        }

        if (CFTagHasArgument(p_CFTag, "expires"))
        {
            expires = CFTagGetArgumentAsString(p_CFTag, "expires");
        }
        else
        {
            value = "\"\"";
        }

        return tabs() + "f_SetCookie(" + name + ", " + value + ", " + expires + ");\n";
    }
    else if(p_CFTag.m_Name.compare("cfdump", Qt::CaseInsensitive) == 0) // TODO: cfdump - Only 'var' parameter is implemented
    {
        if (!CFTagHasArgument(p_CFTag, "var"))
        {
            throw QCFGeneratorException("cfdump var attribute is missing.", p_CFTag.m_Start);
        }

        QString local_vars;

        return tabs() + "f_cfdump(" + GenerateCFExpressionToCExpression(OptimizeQCFParserElement(CFTagGetArgumentObject(p_CFTag, "var").m_ChildElements.at(2)), "", local_vars) + ");\n";
    }
    else if(p_CFTag.m_Name.compare("cfexit", Qt::CaseInsensitive) == 0) // Done
    {
        if (p_CFTag.m_TagType == CFTagType)
        {
            QString method;

            if (CFTagHasArgument(p_CFTag, "method"))
            {
                method = CFTagGetArgumentAsString(p_CFTag, "method");
            }
            else
            {
                method = "exitTag";
            }

            if (method.compare("exitTag", Qt::CaseInsensitive) == 0)
            {
                return tabs() + "return;\n";
            }
            else if (method.compare("exitTemplate", Qt::CaseInsensitive) == 0)
            {
                return tabs() + "return;\n";
            }
            else if (method.compare("loop", Qt::CaseInsensitive) == 0)
            {
                return tabs() + "customTagLoop();\n" + tabs() + "return;\n";
            }
            else
            {
                throw QCFGeneratorException(QString("Invalid cfexit method attribute value[%1]").arg(method), p_CFTag.m_Start);
            }
        }
    }
    else if(p_CFTag.m_Name.compare("cffile", Qt::CaseInsensitive) == 0) // TODO: cffile - Implemented 'action': delete, upload
    {
        const QString &action = CFTagGetArgumentPlain(p_CFTag, "action").toLower();

        if (action == "delete")
        {
            const QString &file = CFTagGetArgument(p_CFTag, "file");

            return tabs() + "cf_FileDelete(" + file + ");\n";
        }
        else if (action == "upload")
        {
            QString destination;
            QString fileField;
            QString accept;
            QString attributes;
            QString mode;
            QString nameConflict;
            QString result;

            if (!CFTagHasArgument(p_CFTag, "destination"))
            {
                throw QCFGeneratorException("At <cffile action=\"upload\" ... > destination parameter is empty or missing.", p_CFTag.m_Start);
            }
            destination = CFTagGetArgumentAsString(p_CFTag, "destination");

            if (!CFTagHasArgument(p_CFTag, "fileField"))
            {
                throw QCFGeneratorException("At <cffile action=\"upload\" ... > fileField parameter is empty or missing.", p_CFTag.m_Start);
            }
            fileField = CFTagGetArgumentAsString(p_CFTag, "fileField");

            if (CFTagHasArgument(p_CFTag, "accept"))
            {
                accept = CFTagGetArgumentAsString(p_CFTag, "destination");
            }
            else
            {
                accept = "QString()";
            }

            if (CFTagHasArgument(p_CFTag, "attributes"))
            {
                attributes = CFTagGetArgumentAsString(p_CFTag, "attributes");
            }
            else
            {
                attributes = "QString()";
            }

            if (CFTagHasArgument(p_CFTag, "mode"))
            {
                mode = CFTagGetArgumentAsString(p_CFTag, "mode");
            }
            else
            {
                mode = "QString()";
            }

            if (CFTagHasArgument(p_CFTag, "nameConflict"))
            {
                nameConflict = CFTagGetArgumentAsString(p_CFTag, "nameConflict");
            }
            else
            {
                nameConflict = "\"Error\"";
            }

            if (CFTagHasArgument(p_CFTag, "result"))
            {
                result = CFTagGetArgumentAsString(p_CFTag, "result");
            }
            else
            {
                result = "QString(\"cffile\")";
            }

            return tabs() + "f_FileUploadMove(" + destination + ", "  + fileField + ", " + accept + ", " + attributes + ", "  + mode + ", " + nameConflict + ", " + result + ");\n";
        }
    }
    else if(p_CFTag.m_Name.compare("cfimport", Qt::CaseInsensitive) == 0)
    {
        if (!CFTagHasArgument(p_CFTag, "taglib"))
        {
            throw QCFGeneratorException("cfimport needs taglib attribute.", p_CFTag.m_Start);
        }

        if (!CFTagHasArgument(p_CFTag, "prefix"))
        {
            throw QCFGeneratorException("cfimport needs prefix attribute.", p_CFTag.m_Start);
        }

        const QString &tagLib = CFTagGetArgumentPlain(p_CFTag, "taglib");
        const QString &prefix = CFTagGetArgumentPlain(p_CFTag, "prefix");

        m_CustomTagsPrefixes.insert(prefix, tagLib);
    }
    else if(p_CFTag.m_Name.compare("cfinclude", Qt::CaseInsensitive) == 0) // Done
    {
        return tabs() + "f_Include(" + CFTagGetArgument(p_CFTag, "template") + ");";
    }
    else if(p_CFTag.m_Name.compare("cfloop", Qt::CaseInsensitive) == 0) // TODO: cfloop - Unimplemented: date or time, query, list or file or array, COM/DCOM collection or structure
    {
        QString ret;

        if (p_CFTag.m_TagType == CFTagType)
        {
            if ((CFTagHasArgument(p_CFTag, "index"))&&(CFTagHasArgument(p_CFTag, "from"))&&(CFTagHasArgument(p_CFTag, "to")))
            {
                QString l_Step;
                QString l_Comparation;

                if (CFTagHasArgument(p_CFTag, "step"))
                {
                    l_Step = CFTagGetArgumentPlain(p_CFTag, "step");
                }
                else
                {
                    l_Step = "1";
                }

                if (l_Step.startsWith('-'))
                {
                    l_Comparation = ">=";
                }
                else
                {
                    l_Comparation = "<=";
                }

                if (CFTagHasArgument(p_CFTag, "step"))
                {
                    l_Step = CFTagGetArgumentAsNumber(p_CFTag, "step");
                }

                QCFParserElement l_Index = CFTagGetArgumentObject(p_CFTag, "index");
                QString l_IndexStr = l_Index.m_ChildElements[2].m_Text;

                if ((l_Index.m_Type != Error)&&(l_Index.m_ChildElements.size() == 3))
                {
                    QString index_var = GenerateVariable(l_IndexStr);

                    ret  = tabs() + "f_Param(QString::fromWCharArray(L\"" + toCPPEncodedString(l_IndexStr.toUpper()) + "\"), QCFVariant(0));\n";
                    ret += tabs() + "for (" + index_var + " = " + CFTagGetArgumentAsNumber(p_CFTag, "from") + "; (" + index_var + ") " + l_Comparation + " (" + CFTagGetArgumentAsNumber(p_CFTag, "to") + "); " + index_var + " = (" + index_var + ") + " + l_Step + ")\n";
                    ret += tabs() + "{\n";

                    m_Tabs++;

                    return ret;
                }
            }
            else if (CFTagHasArgument(p_CFTag, "condition"))
            {
                QCFParserElement l_conditionElement = CFTagGetArgumentObject(p_CFTag, "condition");

                if (l_conditionElement.m_ChildElements.count() == 3)
                {
                    QCFParser parser(CompilerMode, QCFParserTemplateFile);

                    const QString &l_conditionStr = l_conditionElement.m_ChildElements.at(2).m_Text;

                    QCFParserElement l_newConditionElement = parser.ParseCFCode(l_conditionStr, (qint32)0, Expression, nullptr);

                    QString local_vars;

                    ret  = tabs() + "while(" + GenerateCFExpressionToCExpression(OptimizeQCFParserElement(l_newConditionElement), "", local_vars) + ")\n";
                    ret += tabs() + "{\n";

                    m_Tabs++;

                    return ret;
                }

                // TODO: Generate Error.
            }
            else if (CFTagHasArgument(p_CFTag, "query"))
            {
                QString start;
                QString end;

                if (CFTagHasArgument(p_CFTag, "startRow"))
                {
                    start = CFTagGetArgument(p_CFTag, "startRow");
                }
                else
                {
                    start = "1";
                }

                if (CFTagHasArgument(p_CFTag, "endRow"))
                {
                    end = CFTagGetArgument(p_CFTag, "endRow");
                }

                if (!end.isEmpty())
                {
                    ret = tabs() + "for(int i = " + start + "; i <= " + end + "; i++)\n";
                }
                else
                {
                    ret = tabs() + "for(int i = " + start + "; ; i++)\n";
                }

                ret += tabs() + "{\n";

                m_Tabs++;

                ret += tabs() + "QCFVariant l_Query(QCFVariant::Struct);\n";
                ret += tabs() + "if (f_FetchQueryRow(l_Query, " + ParseAndGenerateCppExpressionFromString(CFTagGetArgumentPlain(p_CFTag, "query")) + ", i) == false) break;\n";
                ret += tabs() + "l_Query.m_HiddenScopeLast1 = m_VARIABLES.m_HiddenScopeFirst;\n";
                ret += tabs() + "m_VARIABLES.m_HiddenScopeFirst = &l_Query;\n";

                return ret;
            }
        }

        if (p_CFTag.m_TagType == EndCFTagType)
        {
            if (CFTagHasArgument(*p_CFTag.m_OtherTag, "query"))
            {
                ret += tabs() + "m_VARIABLES.m_HiddenScopeFirst = l_Query.m_HiddenScopeLast1;\n";
            }

            m_Tabs--;

            ret += tabs() + "}";

            return ret;
        }
    }
    else if(p_CFTag.m_Name.compare("cfset", Qt::CaseInsensitive) == 0) // Done
    {
        QString local_vars;

        return tabs() + GenerateCFExpressionToCExpression(p_CFTag.m_Arguments, "", local_vars) + ";\n";
    }
    else if(p_CFTag.m_Name.compare("cfoutput", Qt::CaseInsensitive) == 0) // TODO: cfoutput - Unimplemented attributes: group, groupCaseSensitive
    {
        QString ret;

        if (p_CFTag.m_TagType == CFTagType)
        {
            ret += tabs() + "m_CFOutput++;\n";

            if (CFTagHasArgument(p_CFTag, "query"))
            {
                QString startRow;

                if (CFTagHasArgument(p_CFTag, "startRow"))
                {
                    startRow = CFTagGetArgumentAsString(p_CFTag, "startRow");
                }
                else
                {
                    startRow = "1";
                }

                if (CFTagHasArgument(p_CFTag, "maxRows"))
                {
                    QString maxRowsExpression, maxRows;

                    maxRows = CFTagGetArgumentAsString(p_CFTag, "maxRows");

                    maxRowsExpression = "(" + maxRows + ")";

                    ret += tabs() + "for(int i = " + startRow + "; i < (" + maxRowsExpression + " + " + startRow + "); i++)\n";
                }
                else
                {
                    ret += tabs() + "for(int i = " + startRow + "; ; i++)\n";
                }

                ret += tabs() + "{\n";

                m_Tabs++;

                ret += tabs() + "QCFVariant l_Query(QCFVariant::Struct);\n";
                ret += tabs() + "if (f_FetchQueryRow(l_Query, " + ParseAndGenerateCppExpressionFromString(CFTagGetArgumentPlain(p_CFTag, "query")) + ", i) == false) break;\n";
                ret += tabs() + "l_Query.m_HiddenScopeLast1 = m_VARIABLES.m_HiddenScopeFirst;\n";
                ret += tabs() + "m_VARIABLES.m_HiddenScopeFirst = &l_Query;\n";
            }

            return ret;
        }

        if (p_CFTag.m_TagType == EndCFTagType)
        {
            if (CFTagHasArgument(*p_CFTag.m_OtherTag, "query"))
            {
                ret += tabs() + "m_VARIABLES.m_HiddenScopeFirst = l_Query.m_HiddenScopeLast1;\n";

                m_Tabs--;

                ret += tabs() + "}\n";
            }

            ret += tabs() + "m_CFOutput--;\n";

            return ret;
        }
    }
    else if(p_CFTag.m_Name.compare("cfparam", Qt::CaseInsensitive) == 0) // TODO: cfparam - "name type" variant unimplemented, unimplemented attributes: max, min, pattern
    {
        bool has_name = CFTagHasArgument(p_CFTag, "name");
        bool has_default = CFTagHasArgument(p_CFTag, "default");
        bool has_type = CFTagHasArgument(p_CFTag, "type");

        if ((has_name)&&(has_default))
        {
            return tabs() + "f_Param(" + CFTagGetArgument(p_CFTag, "name") + ", " + CFTagGetArgument(p_CFTag, "default") + ");";
        }
        else if ((has_name)&&(!has_type))
        {
            return tabs() + "f_Param(" + CFTagGetArgument(p_CFTag, "name") + ");";
        }
        else if ((has_name)&&(has_type))
        {
            return tabs() + "unimplemented()";
        }
        else
        {
            return tabs() + "parser error()";
        }
    }
    else if(p_CFTag.m_Name.compare("cfreturn", Qt::CaseInsensitive) == 0) // Done
    {
        QCFParserElement l_OptimizedElements = OptimizeQCFParserElement(p_CFTag.m_Arguments);
        QString local_vars;

        return tabs() + "return " + GenerateCFExpressionToCExpression(l_OptimizedElements, "", local_vars) + ";";
    }
    else if(p_CFTag.m_Name.compare("cfif", Qt::CaseInsensitive) == 0) // Done
    {
        if (p_CFTag.m_TagType == CFTagType)
        {
            QString ret, local_vars;

            ret  = tabs() + "if (" + GenerateCFExpressionToCExpression(p_CFTag.m_Arguments, "", local_vars) + ")\n";
            ret += tabs() + "{\n";

            m_Tabs++;

            return ret;
        }
        if (p_CFTag.m_TagType == EndCFTagType)
        {
            m_Tabs--;

            return tabs() + "}";
        }
    }
    else if(p_CFTag.m_Name.compare("cfelse", Qt::CaseInsensitive) == 0) // Done
    {
        if (p_CFTag.m_TagType == CFTagType)
        {
            return tabs(-1) + "} else {";
        }
    }
    else if(p_CFTag.m_Name.compare("cfelseif", Qt::CaseInsensitive) == 0) // Done
    {
        if (p_CFTag.m_TagType == CFTagType)
        {
            QString local_vars;

            return tabs(-1) + "} else if(" + GenerateCFExpressionToCExpression(p_CFTag.m_Arguments, "", local_vars) + ") {";
        }
    }
    else if(p_CFTag.m_Name.compare("cflocation", Qt::CaseInsensitive) == 0) // TODO: cflocation - "url addToken", "url, statusCode", "url, addToken, statusCode" variants are unimplemented
    {
        if (!CFTagHasArgument(p_CFTag, "url"))
        {
            throw QCFGeneratorException("cflocation tag must have url attribute.", p_CFTag.m_Start);
        }

        if ((!CFTagHasArgument(p_CFTag, "addToken"))&&(!CFTagHasArgument(p_CFTag, "statusCode")))
        {
            return tabs() + "f_Location(" + CFTagGetArgument(p_CFTag, "url") + ");\n";
        }
        else if ((CFTagHasArgument(p_CFTag, "addToken"))&&(!CFTagHasArgument(p_CFTag, "statusCode")))
        {
            throw QCFGeneratorException("cflocation url addToken is NOT implemented.", p_CFTag.m_Start);
        }
        else if ((!CFTagHasArgument(p_CFTag, "addToken"))&&(CFTagHasArgument(p_CFTag, "statusCode")))
        {
            throw QCFGeneratorException("cflocation url, statusCode is NOT implemented.", p_CFTag.m_Start);
        }
        else
        {
            throw QCFGeneratorException("cflocation url, addToken, statusCode is NOT implemented.", p_CFTag.m_Start);
        }
    }
    else if(p_CFTag.m_Name.compare("cfmodule", Qt::CaseInsensitive) == 0) // TODO: attributeCollection not implemented.
    {
        QString ret;

        if (p_CFTag.m_TagType == CFTagType)
        {
            if((CFTagHasArgument(p_CFTag, "name"))&&(CFTagHasArgument(p_CFTag, "template")))
            {
                throw QCFGeneratorException("cfmodule tag can\'t have both name and template attributes.", p_CFTag.m_Start);
            }
            else if(CFTagHasArgument(p_CFTag, "name"))
            {
                const QString &endTag = (p_CFTag.m_OtherTag ? "true" : "false");

                ret += tabs() + "{\n";
                m_Tabs++;

                ret += tabs() + "QCFVariant cftag_attributes(QCFVariant::Struct);\n";

                for(const QCFParserElement &argument : p_CFTag.m_Arguments.m_ChildElements)
                {
                    if ((argument.m_Type == CFTagArgument)&&(argument.m_ChildElements.count() == 3))
                    {
                        const QString &argumentName = argument.m_ChildElements.at(0).m_Text;

                        if (argumentName.compare("name", Qt::CaseInsensitive) != 0)
                        {
                            ret += tabs() + l_worker + "cftag_attributes._()[L\"" + toCPPEncodedString(argumentName.toUpper()) + "\"] = " + CFTagGetArgument(p_CFTag, argumentName) + ");\n";
                        }
                    }
                }

                ret += tabs() + "startCustomTag(\"\", \"" + toCPPEncodedString(CFTagGetArgumentPlain(p_CFTag, "name")) + "\",cftag_attributes, " + endTag + ", QCustomTagTypeModuleName);\n";

                if (p_CFTag.m_OtherTag)
                {
                    ret += tabs() + "do {\n";

                    m_Tabs++;
                }
                else
                {
                    m_Tabs--;
                    ret += tabs() + "}\n";
                }
            }
            else if(CFTagHasArgument(p_CFTag, "template"))
            {
                const QString &endTag = (p_CFTag.m_OtherTag ? "true" : "false");

                ret += tabs() + "{\n";
                m_Tabs++;

                ret += tabs() + "QCFVariant cftag_attributes(QCFVariant::Struct);\n";

                for(const QCFParserElement &argument : p_CFTag.m_Arguments.m_ChildElements)
                {
                    if ((argument.m_Type == CFTagArgument)&&(argument.m_ChildElements.count() == 3))
                    {
                        const QString &argumentName = argument.m_ChildElements.at(0).m_Text;

                        if (argumentName.compare("template", Qt::CaseInsensitive) != 0)
                        {
                            ret += tabs() + l_worker + "cftag_attributes._()[L\"" + toCPPEncodedString(argumentName.toUpper()) + "\"] = " + CFTagGetArgument(p_CFTag, argumentName) + ");\n";
                        }
                    }
                }

                ret += tabs() + "startCustomTag(\"\", \"" + toCPPEncodedString(CFTagGetArgumentPlain(p_CFTag, "template")) + "\", cftag_attributes, " + endTag + ", QCustomTagTypeModuleTemplate);\n";

                if (p_CFTag.m_OtherTag)
                {
                    ret += tabs() + "do {\n";

                    m_Tabs++;
                }
                else
                {
                    m_Tabs--;
                    ret += tabs() + "}\n";
                }
            }
            else
            {
                throw QCFGeneratorException("cfmodule tag must have ether name or template attribute.", p_CFTag.m_Start);
            }
        }
        else
        {
            QString name;
            QString tagType;

            if(CFTagHasArgument(*p_CFTag.m_OtherTag, "name"))
            {
                name = CFTagGetArgumentPlain(*p_CFTag.m_OtherTag, "name");
                tagType = "QCustomTagTypeModuleName";
            }
            else if(CFTagHasArgument(*p_CFTag.m_OtherTag, "template"))
            {
                name = CFTagGetArgumentPlain(*p_CFTag.m_OtherTag, "template");
                tagType = "QCustomTagTypeModuleTemplate";
            }
            else
            {
                throw QCFGeneratorException("cfmodule tag must have ether name or template attribute.", p_CFTag.m_Start);
            }

            m_Tabs--;

            ret = tabs() + "} while(endCustomTag(\"\", \"" + toCPPEncodedString(name) + "\", " + tagType + ") == true);\n";

            m_Tabs--;

            ret += tabs() + "}\n";
        }

        return ret;
    }
    else if(p_CFTag.m_Name.compare("cfsetting", Qt::CaseInsensitive) == 0) // TODO: cfsetting - Unimplemented attributes: requestTimeOut, showDebugOutput
    {
        QString l_enablecfoutputonly = CFTagGetArgumentPlain(p_CFTag, "enablecfoutputonly");
        l_enablecfoutputonly = l_enablecfoutputonly.remove('\'');
        l_enablecfoutputonly = l_enablecfoutputonly.remove('\"');

        if ((l_enablecfoutputonly.compare("true", Qt::CaseInsensitive) == 0)||(l_enablecfoutputonly.compare("yes", Qt::CaseInsensitive)) == 0)
        {
            m_EnableCFOutputOnly = true;
        }
        if ((l_enablecfoutputonly.compare("false", Qt::CaseInsensitive) == 0)||(l_enablecfoutputonly.compare("no", Qt::CaseInsensitive)) == 0)
        {
            m_EnableCFOutputOnly = false;
        }
    }
    else if(p_CFTag.m_Name.compare("cfswitch", Qt::CaseInsensitive) == 0) // Done
    {
        if (p_CFTag.m_TagType == CFTagType)
        {
            m_SwitchTags.append(&p_CFTag);
            m_SwitchCaseCount.append(0);
        }
        else if (p_CFTag.m_TagType == EndCFTagType)
        {
            m_SwitchCaseCount.takeLast();
            m_SwitchTags.takeLast();
        }
    }
    else if(p_CFTag.m_Name.compare("cftry", Qt::CaseInsensitive) == 0) // Done
    {
        QString ret;

        if (p_CFTag.m_TagType == CFTagType)
        {
            ret = tabs() + "try {";

            m_Tabs++;

            return ret;
        }
        else
        {
            m_Tabs--;

            return tabs() + "}";
        }
    }
    else if(p_CFTag.m_Name.compare("cfquery", Qt::CaseInsensitive) == 0) // TODO: cfquery - Implemented attributes: name, datasource
    {
        QString l_queryType;
        QString l_queryName;
        QString l_queryDataSource;

        switch (p_CFTag.m_TagType)
        {
        case CFTagType:
            l_queryType = CFTagGetArgumentPlain(p_CFTag, "type");
            l_queryName = CFTagGetArgumentPlain(p_CFTag, "name");
            l_queryDataSource = CFTagGetArgument(p_CFTag, "datasource");
            break;
        case EndCFTagType:
            l_queryType = CFTagGetArgumentPlain(*p_CFTag.m_OtherTag, "type");
            l_queryName = CFTagGetArgumentPlain(*p_CFTag.m_OtherTag, "name");
            l_queryDataSource = CFTagGetArgument(*p_CFTag.m_OtherTag, "datasource");
            break;
        default:
            break;
        }

        if (((l_queryType.isEmpty())||(l_queryType.compare("query", Qt::CaseInsensitive) == 0))&&(!l_queryName.isEmpty())&&(!l_queryDataSource.isEmpty()))
        {
            if (p_CFTag.m_TagType == CFTagType)
            {
                return tabs() + "startQuery();";
            }

            if (p_CFTag.m_TagType == EndCFTagType)
            {
                // TODO: LOCAL is missing.
                return tabs() + l_worker + "m_VARIABLES._()[L\"" + l_queryName.toUpper() + "\"] = endQuery(" + l_queryDataSource + ");\n";
            }
        }
        else if (((l_queryType.isEmpty())||(l_queryType.compare("query", Qt::CaseInsensitive) == 0))&&(l_queryName.isEmpty())&&(!l_queryDataSource.isEmpty()))
        {
            if (p_CFTag.m_TagType == CFTagType)
            {
                return tabs() + "startQuery();";
            }

            if (p_CFTag.m_TagType == EndCFTagType)
            {
                return tabs() + "endQueryNoReturn(" + l_queryDataSource + ");";
            }
        }
    }
    else if(p_CFTag.m_Name.compare("cfqueryparam", Qt::CaseInsensitive) == 0) // TODO: cfqueryparam - implemented attributes: value
    {
        if (p_CFTag.m_TagType == CFTagType)
        {
            return tabs() + "m_QueryParams.append(" +  CFTagGetArgument(p_CFTag, "value") + "); f_WriteOutput(L\"?\");";
        }
    }
    else if(p_CFTag.m_Name.startsWith("cf_", Qt::CaseInsensitive))
    {
        QString ret;

        if (p_CFTag.m_TagType == CFTagType)
        {
            QString templateName = p_CFTag.m_Name.right(p_CFTag.m_Name.length() - 3).toLower();
            const QString &endTag = (p_CFTag.m_OtherTag ? "true" : "false");

            ret += tabs() + "{\n";
            m_Tabs++;

            ret += tabs() + "QCFVariant cftag_attributes(QCFVariant::Struct);\n";

            for(const QCFParserElement &argument : p_CFTag.m_Arguments.m_ChildElements)
            {
                if ((argument.m_Type == CFTagArgument)&&(argument.m_ChildElements.count() == 3))
                {
                    const QString &argumentName = argument.m_ChildElements.at(0).m_Text;

                    ret += tabs() + l_worker + "cftag_attributes._()[L\"" + toCPPEncodedString(argumentName.toUpper()) + "\"] = " + CFTagGetArgument(p_CFTag, argumentName) + ";\n";
                }
            }

            ret += tabs() + "startCustomTag(\"\", \"" + toCPPEncodedString(templateName) + "\", cftag_attributes, " + endTag + ", QCustomTagType_);\n";

            if (p_CFTag.m_OtherTag)
            {
                ret += tabs() + "do {\n";

                m_Tabs++;
            }
            else
            {
                m_Tabs--;
                ret += tabs() + "}\n";
            }
        }
        else
        {
            QString templateName = p_CFTag.m_OtherTag->m_Name.right(p_CFTag.m_Name.length() - 3).toLower();

            m_Tabs--;

            ret = tabs() + "} while(endCustomTag(\"\", \"" + toCPPEncodedString(templateName) + "\", QCustomTagType_) == true);\n";

            m_Tabs--;

            ret += tabs() + "}\n";
        }

        return ret;
    }
    else if(p_CFTag.m_Name.contains(':'))
    {
        QString ret;

        if (p_CFTag.m_TagType == CFTagType)
        {
            int pos = p_CFTag.m_Name.indexOf(':');

            const QString &prefix = p_CFTag.m_Name.left(pos).toLower();
            const QString &templateName = p_CFTag.m_Name.right(p_CFTag.m_Name.length() - pos - 1).toLower();
            const QString &endTag = (p_CFTag.m_OtherTag ? "true" : "false");

            if (!m_CustomTagsPrefixes.contains(prefix))
            {
                throw QCFGeneratorException("Custom tag prefix is missing. parser error.", p_CFTag.m_Start);
            }

            const QString &path = m_CustomTagsPrefixes[prefix];

            ret += tabs() + "{\n";
            m_Tabs++;

            ret += tabs() + "QCFVariant cftag_attributes(QCFVariant::Struct);\n";

            for(const QCFParserElement &argument : p_CFTag.m_Arguments.m_ChildElements)
            {
                if ((argument.m_Type == CFTagArgument)&&(argument.m_ChildElements.count() == 3))
                {
                    const QString &argumentName = argument.m_ChildElements.at(0).m_Text;

                    ret += tabs() + l_worker + "cftag_attributes._()[L\"" + toCPPEncodedString(argumentName.toUpper()) + "\"] = " + CFTagGetArgument(p_CFTag, argumentName) + ";\n";
                }
            }

            ret += tabs() + "startCustomTag(\"" + toCPPEncodedString(path) + "\", \"" + toCPPEncodedString(templateName) + "\", cftag_attributes, " + endTag + ", QCustomTagTypeImport);\n";

            if (p_CFTag.m_OtherTag)
            {
                ret += tabs() + "do {\n";

                m_Tabs++;
            }
            else
            {
                m_Tabs--;
                ret += tabs() + "}\n";
            }
        }
        else
        {
            int pos = p_CFTag.m_OtherTag->m_Name.indexOf(':');

            const QString &prefix = p_CFTag.m_OtherTag->m_Name.left(pos).toLower();
            const QString &templateName = p_CFTag.m_OtherTag->m_Name.right(p_CFTag.m_Name.length() - pos - 1).toLower();

            if (!m_CustomTagsPrefixes.contains(prefix))
            {
                throw QCFGeneratorException("Custom tag prefix is missing. parser error.", p_CFTag.m_Start);
            }

            const QString &path = m_CustomTagsPrefixes[prefix];

            m_Tabs--;

            ret = tabs() + "} while(endCustomTag(\"" + toCPPEncodedString(path) + "\", \"" + toCPPEncodedString(templateName) + "\", QCustomTagTypeImport) == true);\n";

            m_Tabs--;

            ret += tabs() + "}\n";
        }

        return ret;
    }

    return "";
}

QByteArray QCFGenerator::GenerateWriteOutput(const QString &output)
{
    if (isComponent())
    {
        return "worker.f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodedString(output) + "\", " + QByteArray::number(output.length()) + "));\n";
    }
    else
    {
        return "worker.f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodedString(output) + "\", " + QByteArray::number(output.length()) + "));\n";
    }
}

QString QCFGenerator::tabs(int trim)
{
    QString ret;

    for(int c = 0; c < m_Tabs + trim; c++)
    {
        ret.append('\t');
    }

    return ret;
}

int QCFGenerator::lineFromPosition(int pos)
{
    int ret = 1;
    int offset = 0;

    const QString text = m_Parser.getText();

    forever
    {
        int offset1 = text.indexOf("\r\n", offset);
        int offset2 = text.indexOf("\n", offset);

        if ((offset1 == -1)&&(offset2 == -1))
        {
            break;
        }
        else if ((offset1 != -1)&&(offset2 != -1))
        {
            if (offset1 < offset2)
            {
                offset = offset1 + 2;
            }
            else
            {
                offset = offset2 + 1;
            }
        }
        else if (offset1 != -1)
        {
            offset = offset1 + 2;
        }
        else
        {
            offset = offset2 + 1;
        }

        if (offset > pos)
        {
            break;
        }

        ret++;
    }

    return ret;
}

bool QCFGenerator::isComponent() const
{
    return m_Parser.m_FileType == QCFParserComponentFile;
}
