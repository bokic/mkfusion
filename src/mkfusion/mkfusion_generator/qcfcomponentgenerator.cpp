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
}

void QCFComponentGenerator::generateCpp(const QString &dstFilePath)
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
    l_cppFile.write("class QCFGeneratedComponent : public QCFVariantComponent\n");
    l_cppFile.write("{\n");
    l_cppFile.write("public:\n");
    l_cppFile.write("\tQCFGeneratedComponent(QCFWorkerThread &worker)\n");
    l_cppFile.write("\t\t: QCFVariantComponent()\n");
    l_cppFile.write("\t{\n");

    l_cppFile.write("\t\tm_TemplateFilePath = QString::fromWCharArray(L\"" + toCPPEncodeStr(m_Parser.m_FileName).toUtf8() + "\");\n");
    l_cppFile.write("\t\tm_TemplateFileSize = " + QByteArray::number(m_Parser.m_FileSize) + ";\n");
    l_cppFile.write("\t\tm_TemplateFileModified = " + QByteArray::number(m_Parser.m_FileModifyDateTime) + ";\n");


    // Test chunk.
    l_cppFile.write("\t\tworker.f_WriteOutput(QString(\"Something before data member\"));\n");
    l_cppFile.write("\t\tself[QString::fromWCharArray(L\"key\")] = QString::fromWCharArray(L\"value\");\n");
    l_cppFile.write("\t\tworker.f_WriteOutput(QString(\"Something after data member\"));\n");
    l_cppFile.write("\t\tworker.f_WriteOutput(QString(\"Something before function member\"));\n");
    l_cppFile.write("\t\t//self[L\"function\"] = ;\n");
    l_cppFile.write("\t\tworker.f_WriteOutput(QString(\"Something after function member\"));\n");

    const QList<QCFParserTag> &l_Tags = m_Parser.getTags();

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

                    if ((!m_EnableCFOutputOnly)&&(m_EnableComponentOutput)&&(m_EnableFunctionOutput))
                    {
                        l_cppFile.write(QString(tabs() + "worker.f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
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

                    if ((!m_EnableCFOutputOnly)&&(m_EnableComponentOutput)&&(m_EnableFunctionOutput))
                    {
                        l_cppFile.write(QString(tabs() + "worker.f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
                    }
                }
            }
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
    l_cppFile.write(QString("\treturn QCFTemplateInfo(QString::fromWCharArray(L\"" + toCPPEncodeStr(m_Parser.m_FileName) + "\"), " + QString::number(m_Parser.m_FileSize) + ", " + QString::number(m_Parser.m_FileModifyDateTime) + ");\n").toUtf8());
    l_cppFile.write("};\n");

    if (l_cppFile.error() != QFileDevice::NoError)
    {
        throw QCFGeneratorException(QObject::tr("File operation error: %1.").arg(l_cppFile.errorString()), 0);
    }

    l_cppFile.close();
}
