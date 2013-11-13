#include "qcfcomponentgenerator.h"
#include "qcfgeneratorexception.h"
#include "qcfparser.h"
#include "qcftag.h"

#include <QFileInfo>
#include <QString>
#include <QFile>


QCFComponentGenerator::QCFComponentGenerator()
    : QCFGenerator()
    , m_EnableComponentOutput(true)
    , m_EnableFunctionOutput(true)
{
    m_Parser.m_FileType = QCFParserComponentFile;
}

void QCFComponentGenerator::generateCpp(const QString &dstFilePath)
{
    QFile l_cppFile(dstFilePath);
    l_cppFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    l_cppFile.write("#include <qcfvariantcomponent.h>\n");
    l_cppFile.write("#include <qcfvariantfunction.h>\n");
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
    l_cppFile.write("class QCFGeneratedComponent : public QCFVariantComponent\n");
    l_cppFile.write("{\n");
    l_cppFile.write("public:\n");
    l_cppFile.write("\tQCFGeneratedComponent(QCFWorkerThread &worker)\n");
    l_cppFile.write("\t\t: QCFVariantComponent()\n");
    l_cppFile.write("\t{\n");

    l_cppFile.write("\t\tm_TemplateFilePath = QString::fromWCharArray(L\"" + toCPPEncodedString(m_Parser.m_FileName) + "\");\n");
    l_cppFile.write("\t\tm_TemplateFileSize = " + QByteArray::number(m_Parser.m_FileSize) + ";\n");
    l_cppFile.write("\t\tm_TemplateFileModified = " + QByteArray::number(m_Parser.m_FileModifyDateTime) + ";\n");
    l_cppFile.write("\n");

    const QList<QCFParserTag> &l_Tags = m_Parser.getTags();

    for(const QCFParserTag &function : m_Parser.getTagFunctions(l_Tags))
    {
        QString f_name = CFTagGetArgumentPlain(function, "name");
        QString f_access = CFTagGetArgumentPlain(function, "access");
        QString f_description = CFTagGetArgumentPlain(function, "description");
        QString f_displayName = CFTagGetArgumentPlain(function, "displayName");
        QString f_hint = CFTagGetArgumentPlain(function, "hint");
        QString f_output = CFTagGetArgumentPlain(function, "output");
        QString f_returnFormat = CFTagGetArgumentPlain(function, "returnFormat");
        QString f_returnType = CFTagGetArgumentPlain(function, "returnType");
        QString f_roles = CFTagGetArgumentPlain(function, "roles");
        QString f_secureJSON = CFTagGetArgumentPlain(function, "secureJSON");
        QString f_verifyClient = CFTagGetArgumentPlain(function, "verifyClient");
        QString f_args;

        for(const QCFParserTag &arg : m_Parser.getFunctionArguments(function))
        {
            QString a_name = CFTagGetArgumentPlain(arg, "name");
            QString a_default = CFTagGetArgumentPlain(arg, "default");
            QString a_displayname = CFTagGetArgumentPlain(arg, "displayname");
            QString a_hint = CFTagGetArgumentPlain(arg, "hint");
            QString a_required = CFTagGetArgumentPlain(arg, "required");
            QString a_type = CFTagGetArgumentPlain(arg, "type");

            f_args.append("\n\t\t\t\t<< QCFVariantArgument(");

            f_args.append("QString::fromWCharArray(L\"" + toCPPEncodedString(a_name) + "\"), ");
            f_args.append("QString::fromWCharArray(L\"" + toCPPEncodedString(a_default) + "\"), ");
            f_args.append("QString::fromWCharArray(L\"" + toCPPEncodedString(a_displayname) + "\"), ");
            f_args.append("QString::fromWCharArray(L\"" + toCPPEncodedString(a_hint) + "\"), ");
            f_args.append("QString::fromWCharArray(L\"" + toCPPEncodedString(a_required) + "\"), ");
            f_args.append("QString::fromWCharArray(L\"" + toCPPEncodedString(a_type) + "\")");

            f_args.append(")");
        }

        l_cppFile.write("\t\tQCFWorkerThread::updateVariable(self, QString::fromWCharArray(L\"" + toCPPEncodedString(f_name).toUpper() + "\"), QCFVariantFunction(\n");
        l_cppFile.write("\t\t\tQString::fromWCharArray(L\"" + toCPPEncodedString(f_name) + "\"), // Name\n");
        l_cppFile.write("\t\t\tQString::fromWCharArray(L\"" + toCPPEncodedString(f_access) + "\"), // Access\n");
        l_cppFile.write("\t\t\tQString::fromWCharArray(L\"" + toCPPEncodedString(f_description) + "\"), // Description\n");
        l_cppFile.write("\t\t\tQString::fromWCharArray(L\"" + toCPPEncodedString(f_displayName) + "\"), // Display Name\n");
        l_cppFile.write("\t\t\tQString::fromWCharArray(L\"" + toCPPEncodedString(f_hint) + "\"), // Hint\n");
        l_cppFile.write("\t\t\tQString::fromWCharArray(L\"" + toCPPEncodedString(f_output) + "\"), // Output\n");
        l_cppFile.write("\t\t\tQString::fromWCharArray(L\"" + toCPPEncodedString(f_returnFormat) + "\"), // Return Format\n");
        l_cppFile.write("\t\t\tQString::fromWCharArray(L\"" + toCPPEncodedString(f_returnType) + "\"), // Return Type\n");
        l_cppFile.write("\t\t\tQString::fromWCharArray(L\"" + toCPPEncodedString(f_roles) + "\"), // Roles\n");
        l_cppFile.write("\t\t\tQString::fromWCharArray(L\"" + toCPPEncodedString(f_secureJSON) + "\"), // Secure JSON\n");
        l_cppFile.write("\t\t\tQString::fromWCharArray(L\"" + toCPPEncodedString(f_verifyClient) + "\"), // Verify Client\n");
        l_cppFile.write("\t\t\tQCFVariantArgumentList()" + f_args.toUtf8() + ", // Arguments\n");
        l_cppFile.write("\t\t\t[](QCFVariant &self, QCFWorkerThread &worker, QCFVariant &arguments) -> QCFVariant {\n");

        bool is_last_tag_cfreturn = false;

        if (function.m_OtherTag)
        {
            bool found_start = false;

            for(int c = 0; c < l_Tags.count(); c++)
            {
                if (!found_start)
                {
                    if (function == l_Tags.at(c))
                    {
                        found_start = true;
                    }

                    continue;
                }

                if (*function.m_OtherTag == l_Tags.at(c))
                {
                    break;
                }

                QString l_CFromCFTag = GenerateCCodeFromCFTag(l_Tags[c]);
                if (!l_CFromCFTag.isEmpty())
                {
                    l_cppFile.write("\n");
                    l_cppFile.write(QString(tabs(2) + "// Line %1.\n").arg(l_Tags[c].m_Start).toUtf8());
                    l_cppFile.write(QString("\t\t" + l_CFromCFTag + "\n").toUtf8());
                }

                if ((l_Tags[c].m_TagType == CFTagType)&&(l_Tags[c].m_Name.compare("cfreturn", Qt::CaseInsensitive) == 0))
                {
                    is_last_tag_cfreturn = true;
                }
                else
                {
                    is_last_tag_cfreturn = false;
                }
            }
        }

        if (!is_last_tag_cfreturn)
        {
            l_cppFile.write("\n\t\t\t\treturn QCFVariant();\n");
        }

        l_cppFile.write("\t\t\t}));\n\n");
    }

    /*for(const QCFParserElement &function : m_Parser.getScriptFunctions(l_Tags))
    {

    }*/

    QString l_Text = m_Parser.getText();
    QString l_tmpStr;

    qint32 l_CFCodeInsideTags = 0;
    bool output_text = true;

    if ((!l_Tags.isEmpty())&&(output_text))
    {
        l_tmpStr = l_Text.left(l_Tags.first().m_Start);

        if ((!l_tmpStr.isEmpty())&&(!m_EnableCFOutputOnly)&&(m_EnableComponentOutput)&&(m_EnableFunctionOutput))
        {
            l_cppFile.write(tabs().toUtf8() + GenerateWriteOutput(l_tmpStr));
        }
    }

    m_Tabs = 2;

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

        if (c > 0)
        {
            int left = l_Tags.at(c - 1).m_Start + l_Tags.at(c - 1).m_Length;
            int right = l_Tags.at(c).m_Start;

            l_tmpStr = l_Text.mid(left, right - left);

            if ((!l_tmpStr.isEmpty())&&(!m_EnableCFOutputOnly)&&(m_EnableComponentOutput)&&(m_EnableFunctionOutput))
            {
                l_cppFile.write(tabs().toUtf8() + GenerateWriteOutput(l_tmpStr));
            }
        }

        QString l_CFromCFTag = GenerateCCodeFromCFTag(l_Tags[c]);
        if (!l_CFromCFTag.isEmpty())
        {
            l_cppFile.write("\n");
            l_cppFile.write(QString(tabs() + "// Line %1.\n").arg(l_Tags[c].m_Start).toUtf8());
            l_cppFile.write(QString(l_CFromCFTag + "\n").toUtf8());
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

    if ((!l_Tags.isEmpty())&&(output_text))
    {
        l_tmpStr = l_Text.right(l_Text.length() - l_Tags.last().m_Start - l_Tags.last().m_Length);

        if ((!l_tmpStr.isEmpty())&&(!m_EnableCFOutputOnly)&&(m_EnableComponentOutput)&&(m_EnableFunctionOutput))
        {
            l_cppFile.write(tabs().toUtf8() + GenerateWriteOutput(l_tmpStr));
        }
    }

    l_cppFile.write("\t}\n");
    l_cppFile.write("};\n");
    l_cppFile.write("\n");
    l_cppFile.write("extern \"C\" MY_EXPORT QCFVariantComponent createComponent(QCFWorkerThread &worker)\n");
    l_cppFile.write("{\n");
    l_cppFile.write("\treturn QCFGeneratedComponent(worker);\n");
    l_cppFile.write("};\n");
    l_cppFile.write("\n");
    l_cppFile.write("extern \"C\" MY_EXPORT QCFTemplateInfo getTemplateInfo()\n");
    l_cppFile.write("{\n");
    l_cppFile.write(QString("\treturn QCFTemplateInfo(QString::fromWCharArray(L\"" + toCPPEncodedString(m_Parser.m_FileName) + "\"), " + QString::number(m_Parser.m_FileSize) + ", " + QString::number(m_Parser.m_FileModifyDateTime) + ");\n").toUtf8());
    l_cppFile.write("};\n");

    if (l_cppFile.error() != QFileDevice::NoError)
    {
        throw QCFGeneratorException(QObject::tr("File operation error: %1.").arg(l_cppFile.errorString()), 0);
    }

    l_cppFile.close();
}
