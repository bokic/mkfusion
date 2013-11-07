#include "qcftemplategenerator.h"
#include "qcfgeneratorexception.h"
#include "qcfparser.h"
#include "qcftag.h"

#include <QFileInfo>
#include <QString>
#include <QFile>


QCFTemplateGenerator::QCFTemplateGenerator(QObject *parent)
    : QCFGenerator(parent)
{
}

void QCFTemplateGenerator::generateCpp(const QString &dstFilePath)
{
    QFile l_cppFile(dstFilePath);
    l_cppFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    l_cppFile.write("#include <qmkfusionexception.h>\n");
    l_cppFile.write("#include <qcfworkerthread.h>\n");
    l_cppFile.write("#include <qcftemplateinfo.h>\n");
    l_cppFile.write("#include <cffunctions.h>\n");
    l_cppFile.write("#include <qcfvariant.h>\n");
    l_cppFile.write("\n");
    l_cppFile.write("\n");
    l_cppFile.write("#ifdef Q_OS_WIN\n");
    l_cppFile.write("#define MY_EXPORT __declspec(dllexport)\n");
    l_cppFile.write("#else\n");
    l_cppFile.write("#define MY_EXPORT\n");
    l_cppFile.write("#endif\n");
    l_cppFile.write("\n");
    l_cppFile.write("class QCFGeneratedWorkerThread : public QCFWorkerThread\n");
    l_cppFile.write("{\n");
    l_cppFile.write("public:\n");
    l_cppFile.write("\tQCFGeneratedWorkerThread()\n");
    l_cppFile.write("\t\t: QCFWorkerThread()\n");
    l_cppFile.write("\t{\n");

    l_cppFile.write("\t\tm_TemplateFilePath = QString::fromWCharArray(L\"" + toCPPEncodeStr(m_Parser.m_FileName).toUtf8() + "\");\n");
    l_cppFile.write("\t\tm_TemplateFileSize = " + QByteArray::number(m_Parser.m_FileSize) + ";\n");
    l_cppFile.write("\t\tm_TemplateFileModified = " + QByteArray::number(m_Parser.m_FileModifyDateTime) + ";\n");

    const QList<QCFParserTag> &l_Tags = m_Parser.getTags();

    for(const QCFParserTag &function : m_Parser.getTagFunctions(l_Tags))
    {

    }

    for(const QCFParserElement &function : m_Parser.getScriptFunctions(l_Tags))
    {
        QString f_name;
        QString f_returnType;
        QString f_roles;
        QString f_access = "public";
        QString f_output;
        QString f_displayName;
        QString f_hint;
        QString f_description;

        QStringList f_paramName;
        QStringList f_paramRequired;
        QStringList f_paramType;
        QStringList f_paramDefault;

        int pos = 0;

        if (function.m_ChildElements.last().m_Type != CodeBlock)
        {
            throw QCFGeneratorException("Missing function body.", function.m_ChildElements.last().m_Position);
        }

        if (
                (function.m_ChildElements.at(pos).m_Type == Variable)&&
                (
                (function.m_ChildElements.at(pos).m_Text.compare("public", Qt::CaseInsensitive) == 0)||
                (function.m_ChildElements.at(pos).m_Text.compare("private", Qt::CaseInsensitive) == 0)||
                (function.m_ChildElements.at(pos).m_Text.compare("package", Qt::CaseInsensitive) == 0)||
                (function.m_ChildElements.at(pos).m_Text.compare("remote", Qt::CaseInsensitive) == 0)
                )
            )
        {
            f_access = function.m_ChildElements.at(pos).m_Text.toLower();

            pos++;
        }

        if (function.m_ChildElements.at(pos).m_Type == Variable)
        {
            f_returnType = function.m_ChildElements.at(pos).m_Text;

            pos++;
        }

        if ((function.m_ChildElements.at(pos).m_Type != Keyword)||(function.m_ChildElements.at(pos).m_Text.compare("function", Qt::CaseInsensitive) != 0))
        {
            // TODO: Warning. Validator should not pass this case.

            continue;
        }

        pos++;

        if (function.m_ChildElements.at(pos).m_Type != Function)
        {
            // TODO: Warning. Validator should not pass this case.

            continue;
        }

        f_name = function.m_ChildElements.at(pos).m_Text;

        // parameters.
        if (function.m_ChildElements.at(pos).m_ChildElements.count() > 0)
        {
            const QCFParserElement &parameters = function.m_ChildElements.at(pos).m_ChildElements.at(0);
            for(const QCFParserElement &parameter : parameters.m_ChildElements)
            {
                QString name;
                QString required;
                QString type;
                QString def;

                if (parameter.m_ChildElements.at(0).m_ChildElements.count() == 0)
                {
                    if (parameter.m_ChildElements.at(0).m_Type != Variable)
                    {
                        throw QCFGeneratorException("function parameter must be variable.", parameter.m_ChildElements.at(0).m_Position);
                    }

                    name = parameter.m_ChildElements.at(0).m_Text.toUpper();
                }
                else
                {
                    // TODO: Implement CFML function describers.
                    throw QCFGeneratorException("Not implemented(TODO).", parameter.m_ChildElements.at(0).m_Position);
                }

                f_paramName.append(name);
                f_paramRequired.append(required);
                f_paramType.append(type);
                f_paramDefault.append(def);
            }
        }

        pos++;

        // TODO: Implement this when possible(not urgent).

        l_cppFile.write(QString("\t\taddCustomFunction(\"" + toCPPEncodeStr(f_name.toLower()) + "\", [](QCFRunningTemplate *m_TemplateInstance, const QList<QCFVariant> &arguments) -> QCFVariant {\n").toUtf8());

        l_cppFile.write("\t\t\tQCFVariant ARGUMENTS(QCFVariant::Struct);\n");
        l_cppFile.write("\t\t\tQCFVariant LOCAL(QCFVariant::Struct);\n");
        l_cppFile.write("\n");

        // Parameters
        for(int c = 0; c < f_paramName.count(); c++)
        {

            l_cppFile.write(QString("\t\t\tif(arguments.count() > "+ QString::number(c) + " ) {\n").toUtf8());
            l_cppFile.write(QString("\t\t\t\tupdateVariable(ARGUMENTS, L\"" + f_paramName[c].toUpper() + "\", arguments.at(" + QString::number(c) + "));\n").toUtf8());
            l_cppFile.write(QString("\t\t\t} else {\n").toUtf8());
            l_cppFile.write(QString("\t\t\t\tupdateVariable(ARGUMENTS, L\"" + f_paramName[c].toUpper() + "\", L\"" + f_paramDefault[c] + "\");\n").toUtf8());
            l_cppFile.write(QString("\t\t\t}\n").toUtf8());
            l_cppFile.write("\n");
        }

        QString l_localVars;
        for(const QCFParserElement &expr : function.m_ChildElements.last().m_ChildElements)
        {
            l_cppFile.write(QString("\t\t\t" + GenerateCFExpressionToCExpression(expr, f_paramName.join(","), &l_localVars)).toUtf8());

            if ((expr.m_Type == Expression)&&(expr.m_ChildElements.count() > 0))
            {
                if (expr.m_ChildElements.last().m_Type != CodeBlock)
                {
                    l_cppFile.write(";");
                }
            }

            l_cppFile.write("\n");
        }

        l_cppFile.write("\t\t\treturn QCFVariant();\n"); // just in case custom function do not return.

        l_cppFile.write("\t\t});\n");
    }

    l_cppFile.write("\t}\n");
    l_cppFile.write("\n");
    l_cppFile.write("\tvirtual void executePage()\n");
    l_cppFile.write("\t{\n"); // mybase::myfunc() ;

    QString l_Text = m_Parser.getText();
    QString l_tmpStr;

    qint32 l_CFCodeInsideTags = 0;
    bool output_text = true;

    for(int c = 0; c < l_Tags.size(); c++)
    {
        // skip code generation from within cffunction and cfscript.
        if ((l_Tags.at(c).m_TagType == CFTagType)&&((l_Tags.at(c).m_Name == "cffunction")||(l_Tags.at(c).m_Name == "cfscript")))
        {
            struct QCFParserTag *othertag = l_Tags.at(c).m_OtherTag;
            int other = l_Tags.indexOf(*othertag);

            if (other > c)
            {
                c = other;
            }

            continue;
        }

        if (output_text)
        {
            if (c == 0)
            {
                if (l_Tags[0].m_Start > 0)
                {
                    l_tmpStr = l_Text.left(l_Tags[0].m_Start);

                    if (l_CFCodeInsideTags > 0)
                    {
                        l_tmpStr.replace("##", "#");
                    }

                    if (!m_EnableCFOutputOnly)
                    {
                        l_cppFile.write(QString(tabs() + "f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
                    }
                }
            }
            else
            {
                if (l_Tags[c].m_Start - (l_Tags[c - 1].m_Start + l_Tags[c - 1].m_Length) > 0)
                {
                    l_tmpStr = l_Text.mid(l_Tags[c - 1].m_Start + l_Tags[c - 1].m_Length, l_Tags[c].m_Start - l_Tags[c - 1].m_Start - l_Tags[c - 1].m_Length);

                    if (l_CFCodeInsideTags > 0)
                    {
                        l_tmpStr.replace("##", "#");
                    }

                    if (!m_EnableCFOutputOnly)
                    {
                        l_cppFile.write(QString(tabs() + "f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
                    }
                }
            }
        }

        QString l_CFromCFTag = GenerateCCodeFromCFTag(l_Tags[c]);
        if (!l_CFromCFTag.isEmpty())
        {
            l_cppFile.write("\n");
            l_cppFile.write(QString(tabs() + "// Line %1.\n").arg(l_Tags[c].m_Start).toUtf8());
            l_cppFile.write(QString(tabs() + l_CFromCFTag + "\n").toUtf8());
        }

        output_text = true;

        if (m_NestedTags.count() > 0)
        {
            if (m_NestedTags.last()->m_Name.compare("cfswitch", Qt::CaseInsensitive) == 0)
            {
                output_text = false;
            }
        }

        if ((output_text)&&(QCF8::generateCFTags().contains(l_Tags[c].m_Name))&&(QCF8::generateCFTags()[l_Tags[c].m_Name].m_ExpressionInside == QCFTag::WithExpressionInside))
        {
            if ((l_Tags[c].m_TagType == CFTagType)&&(l_Tags[c].m_InlineClosedTag == false))
            {
                l_CFCodeInsideTags++;
            }
            else if (l_Tags[c].m_TagType == EndCFTagType)
            {
                l_CFCodeInsideTags--;
            }
        }
    }

    if (l_Tags.size() == 0)
    {

        l_tmpStr = l_Text;

        if (l_CFCodeInsideTags > 0)
        {
            l_tmpStr.replace("##", "#");
        }

        if (!m_EnableCFOutputOnly)
        {
            l_cppFile.write(QString(tabs() + "f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
        }
    }
    else
    {
        if (l_Text.size() > l_Tags.last().m_Start + l_Tags.last().m_Length)
        {
            l_tmpStr = l_Text.right(l_Text.length() - l_Tags.last().m_Start - l_Tags.last().m_Length);

            if (l_CFCodeInsideTags > 0)
            {
                l_tmpStr.replace("##", "#");
            }

            if (!m_EnableCFOutputOnly)
            {
                l_cppFile.write(QString(tabs() + "f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
            }
        }
    }

    l_cppFile.write("\t}\n");
    l_cppFile.write("};\n");
    l_cppFile.write("\n");
    l_cppFile.write("extern \"C\" MY_EXPORT QCFWorkerThread * createTemplate()\n");
    l_cppFile.write("{\n");
    l_cppFile.write("\treturn new QCFGeneratedWorkerThread();\n");
    l_cppFile.write("};\n");
    l_cppFile.write("\n");
    l_cppFile.write("extern \"C\" MY_EXPORT QCFTemplateInfo getTemplateInfo()\n");
    l_cppFile.write("{\n");
    l_cppFile.write(QString("\treturn QCFTemplateInfo(QString::fromWCharArray(L\"" + toCPPEncodeStr(m_Parser.m_FileName) + "\"), " + QString::number(m_Parser.m_FileSize) + ", " + QString::number(m_Parser.m_FileModifyDateTime) + ");\n").toUtf8());
    l_cppFile.write("};\n");

    if (l_cppFile.error() != QFileDevice::NoError)
    {
        throw QCFGeneratorException(QObject::tr("File operation error: %1.").arg(l_cppFile.errorString()), 0);
    }

    l_cppFile.close();
}
