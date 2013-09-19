#include "qcfgenerator.h"
#include "qcfserver.h"
#include "qcfparser.h"
#include "qcf8.h"

#include <QDateTime>
#include <QProcess>
#include <QList>
#include <QDir>


QCFGenerator::QCFGenerator()
    : m_CFTagsDef(QCF8::generateCFTags())
    , m_CFFunctionsDef(QCF8::generateCFFunctions())
    , m_EnableCFOutputOnly(false)
    , m_Tabs("\t\t")
{
}

QString QCFGenerator::toCPPEncodeStr(const QString &str)
{
    QString ret;

    for(const QChar &qch : str)
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
            ret.append(QChar(ch));
            continue;
        }

        QString tmp = QString::number(ch, 16);

        while(tmp.length() < 4)
        {
            tmp.prepend('0');
        }

        tmp.prepend("\\x");

        ret.append(tmp);
    }

    return ret;
}

QString QCFGenerator::compile(QCFParser &p_Parser, const QString &p_Target, const QString &p_MKFusionPath)
{
	QFileInfo file(p_Target);
	QString l_NewTarget = file.baseName();

	QHash<QString, QCFTag> l_cf8tags = QCF8::generateCFTags();

	QFile l_cppFile(p_MKFusionPath+"templates/"+ l_NewTarget + ".cpp");
	l_cppFile.open(QIODevice::WriteOnly);
	l_cppFile.write("#include \"qmkfusionexception.h\"\n");
	l_cppFile.write("#include \"qcfrunningtemplate.h\"\n");
	l_cppFile.write("#include \"qcftemplate.h\"\n");
	l_cppFile.write("#include \"cffunctions.h\"\n");
	l_cppFile.write("#include \"common.h\"\n");
	l_cppFile.write("\n");
    l_cppFile.write("#ifdef Q_OS_WIN\n");
	l_cppFile.write("#define MY_EXPORT __declspec(dllexport)\n");
	l_cppFile.write("#else\n");
	l_cppFile.write("#define MY_EXPORT\n");
	l_cppFile.write("#endif\n");
	l_cppFile.write("\n");
	l_cppFile.write("class QCFGeneratedTemplate : public QCFTemplate\n");
	l_cppFile.write("{\n");
	l_cppFile.write("public:\n");
	l_cppFile.write("	QCFGeneratedTemplate()\n");
	l_cppFile.write("	{\n");
    l_cppFile.write(QString("		m_isModified.m_Filename = QString::fromWCharArray(L\"" + toCPPEncodeStr(p_Parser.m_FileName) + "\");\n").toUtf8());
    l_cppFile.write(QString("		m_isModified.m_Size = " + QString::number(p_Parser.m_CFMFileSize) + ";\n").toUtf8());
    l_cppFile.write(QString("		m_isModified.m_Modified = " + QString::number(p_Parser.m_CFMModifyDateTime) + ";\n").toUtf8());
    l_cppFile.write("\n");

    QList<QCFParserTag> const l_Tags = p_Parser.getTags();

    /*for(const QCFParserTag &function : p_Parser.getTagFunctions(l_Tags))
    {

    }*/

    for(const QCFParserElement &function : p_Parser.getScriptFunctions(l_Tags))
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
            throw QMKFusionException("Missing function body.");
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
                        throw QMKFusionException("function parameter must be variable.");
                    }

                    name = parameter.m_ChildElements.at(0).m_Text.toUpper();
                }
                else
                {
                    // TODO: Implement me.
                    throw QMKFusionException("Not implemented.");
                }

                f_paramName.append(name);
                f_paramRequired.append(required);
                f_paramType.append(type);
                f_paramDefault.append(def);
            }
        }

        pos++;

        // TODO: Implement this when possible(not urgent).

        l_cppFile.write(QString("       addCustomFunction(\"" + toCPPEncodeStr(f_name.toLower()) + "\", [](QCFRunningTemplate *m_TemplateInstance, const QList<QWDDX> &arguments) -> QWDDX {\n").toUtf8());

        l_cppFile.write("            QWDDX ARGUMENTS(QWDDX::Struct);\n");
        l_cppFile.write("            QWDDX LOCAL(QWDDX::Struct);\n");
        l_cppFile.write("\n");

        // Parameters
        for(int c = 0; c < f_paramName.count(); c++)
        {

            l_cppFile.write(QString("            if(arguments.count() > "+ QString::number(c) + " ) {\n").toUtf8());
            l_cppFile.write(QString("                updateVariable(ARGUMENTS, L\"" + f_paramName[c].toUpper() + "\", arguments.at(" + QString::number(c) + "));\n").toUtf8());
            l_cppFile.write(QString("            } else {\n").toUtf8());
            l_cppFile.write(QString("                updateVariable(ARGUMENTS, L\"" + f_paramName[c].toUpper() + "\", L\"" + f_paramDefault[c] + "\");\n").toUtf8());
            l_cppFile.write(QString("            }\n").toUtf8());
            l_cppFile.write("\n");
        }

        QString l_localVars;
        for(const QCFParserElement &expr : function.m_ChildElements.last().m_ChildElements)
        {
            l_cppFile.write(QString("            " + GenerateCFExpressionToCExpression(expr, f_paramName.join(","), &l_localVars)).toUtf8());

            if ((expr.m_Type == Expression)&&(expr.m_ChildElements.count() > 0))
            {
                if (expr.m_ChildElements.last().m_Type != CodeBlock)
                {
                    l_cppFile.write(";");
                }
            }

            l_cppFile.write("\n");
        }

        l_cppFile.write("            return QWDDX();\n"); // just in case custom function do not return.

        l_cppFile.write("        });\n");
    }

	l_cppFile.write("	}\n");
	l_cppFile.write("	\n");
    l_cppFile.write("	virtual void run(QCFRunningTemplate *p_TemplateInstance)\n");
	l_cppFile.write("	{\n"); // mybase::myfunc() ;
	l_cppFile.write("		QCFTemplate::run(p_TemplateInstance);\n");

	QString l_Text = p_Parser.getText();
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
                        l_cppFile.write(QString(m_Tabs + "f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
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
                        l_cppFile.write(QString(m_Tabs + "f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
                    }
                }
            }
        }

		QString l_CFromCFTag = GenerateCCodeFromCFTag(l_Tags[c]);
		if (!l_CFromCFTag.isEmpty())
		{
            l_cppFile.write(QString("\n" + m_Tabs + "// Line %1.\n").arg(l_Tags[c].m_Start).toUtf8());
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

        if ((output_text)&&(l_cf8tags.contains(l_Tags[c].m_Name))&&(l_cf8tags[l_Tags[c].m_Name].m_ExpressionInside == QCFTag::WithExpressionInside))
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
            l_cppFile.write(QString(m_Tabs + "f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
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
                l_cppFile.write(QString(m_Tabs + "f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
			}
		}
	}

	l_cppFile.write("	}\n");
	l_cppFile.write("};\n");
	l_cppFile.write("\n");
	l_cppFile.write("extern \"C\" MY_EXPORT QCFTemplate* createCFMTemplate()\n");
	l_cppFile.write("{\n");
	l_cppFile.write("	return new QCFGeneratedTemplate();\n");
	l_cppFile.write("};\n");
	l_cppFile.close();

	QProcess process;

	// Compile
#ifdef Q_OS_WIN
    QString l_QtPath = QDir::toNativeSeparators(p_MKFusionPath) + "bin\\qt\\";
    QString l_MingwPath = QDir::toNativeSeparators(p_MKFusionPath) + "bin\\mingw\\";

#ifdef QT_NO_DEBUG
    process.start("\"" + l_MingwPath+"bin\\g++.exe\" -c -O2 -std=c++0x -frtti -fexceptions -mthreads -Wall -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_NO_DEBUG -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I\""+l_MingwPath+"include\" -I\""+l_QtPath+"include\\QtCore\" -I\""+l_QtPath+"include\\QtNetwork\" -I\""+l_QtPath+"include\\QtConcurrent\" -I\""+l_QtPath+"include\" -I\""+p_MKFusionPath+"include\" -o\""+p_MKFusionPath+"templates\\"+l_NewTarget+".o\" \""+p_MKFusionPath+"templates\\"+l_NewTarget+".cpp\"");
#else
    process.start("\"" + l_MingwPath+"bin\\g++.exe\" -c -g -std=c++0x -frtti -fexceptions -mthreads -Wall -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I\""+l_MingwPath+"include\" -I\""+l_QtPath+"include\\QtCore\" -I\""+l_QtPath+"include\\QtNetwork\" -I\""+l_QtPath+"include\\QtConcurrent\" -I\""+l_QtPath+"include\" -I\""+p_MKFusionPath+"include\" -o\""+p_MKFusionPath+"templates\\"+l_NewTarget+".o\" \""+p_MKFusionPath+"templates\\"+l_NewTarget+".cpp\"");
#endif // #ifdef QT_NO_DEBUG
#elif defined Q_OS_LINUX
#ifdef QT_NO_DEBUG
    process.start("g++ -c -m64 -pipe -O2 -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_NO_DEBUG -DQT_CORE_LIB -DQT_SHARED -I/usr/share/qt5/mkspecs/linux-g++-64 -I. -I/usr/include/qt5/QtCore -I/usr/include/qt5/QtNetwork -I/usr/include/qt5/QtConcurrent -I/usr/include/qt5 -I\""+p_MKFusionPath+"include\" -o \""+p_MKFusionPath+"templates/"+l_NewTarget+".o\" \""+p_MKFusionPath+"templates/"+l_NewTarget+".cpp\"");
#else
    process.start("g++ -c -m64 -pipe -g -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_CORE_LIB -DQT_SHARED -I/usr/share/qt5/mkspecs/linux-g++-64 -I. -I/usr/include/qt5/QtCore -I/usr/include/qt5/QtNetwork -I/usr/include/qt5/QtConcurrent -I/usr/include/qt5 -I\""+p_MKFusionPath+"include\" -o \""+p_MKFusionPath+"templates/"+l_NewTarget+".o\" \""+p_MKFusionPath+"templates/"+l_NewTarget+".cpp\"");
#endif // #ifdef QT_NO_DEBUG
#else
#error Windows and Linux OSs are currently supported.
#endif // #ifdef Q_OS_WIN

    bool finished = process.waitForFinished(-1);

#ifdef QT_NO_DEBUG
    QFile::remove(p_MKFusionPath+"templates/"+l_NewTarget+".cpp");
#endif

	if ((finished == false)||(process.exitCode() != 0))
	{
		return "compile error: " + QString::fromUtf8(process.readAllStandardError()) + QString::fromUtf8(process.readAllStandardOutput());
	}

	// Link
#ifdef Q_OS_WIN
#ifdef QT_NO_DEBUG
    process.start("\"" + l_MingwPath+"bin\\g++.exe\" -Wl,-enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc -Wl,-s -mthreads -shared -o\""+p_MKFusionPath+"templates\\"+l_NewTarget+".dll\" \""+p_MKFusionPath+"templates\\"+l_NewTarget+".o\" -L\""+l_QtPath+"lib\" \""+p_MKFusionPath+"lib\\mkfusion.a\" -lQt5Core");
#else
    process.start("\"" + l_MingwPath+"bin\\g++.exe\" -Wl,-enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc -mthreads -shared -o\""+p_MKFusionPath+"templates\\"+l_NewTarget+".dll\" \""+p_MKFusionPath+"templates\\"+l_NewTarget+".o\" -L\""+l_QtPath+"lib\" \""+p_MKFusionPath+"lib\\mkfusion.a\" -lQt5Cored");
#endif
#elif defined Q_OS_LINUX
#ifdef QT_NO_DEBUG
    process.start("g++ -m64 -Wl,-O1 -shared -o \""+p_MKFusionPath+"templates/"+l_NewTarget+".so\" \""+p_MKFusionPath+"templates/"+l_NewTarget+".o\" -L/usr/lib/x86_64-linux-gnu -lQt5Concurrent -lrt -lQt5Core -lpthread");
#else
    process.start("g++ -m64 -shared -o \""+p_MKFusionPath+"templates/"+l_NewTarget+".so\" \""+p_MKFusionPath+"templates/"+l_NewTarget+".o\" -L/usr/lib/x86_64-linux-gnu -lQt5Concurrent -lrt -lQt5Core -lpthread");
#endif
#else
#error Windows and Linux OSs are currently supported.
#endif
    finished = process.waitForFinished(-1);

	QFile::remove(p_MKFusionPath+"templates/"+l_NewTarget+".o");

	if ((finished == false)||(process.exitCode() != 0))
	{
		return "link error: " + process.readAllStandardError() + process.readAllStandardOutput();
	}

	return "";
}

QString QCFGenerator::GenerateVariable(const QString &p_Variable, const QString &p_Funct_params, const QString &p_Funct_local_vars)
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
            ret = "(*m_TemplateInstance->m_" + l_StrList.first() + ")";
        }
        else
        {
            ret = "m_TemplateInstance->m_" + l_StrList.first();
        }
    }

	for(int c = 1; c < l_StrList.size(); c++)
	{
        ret += "[L\"" + l_StrList[c] + "\"]";
	}

	return ret;
}

QString QCFGenerator::GenerateCFExpressionToCExpression(const QCFParserElement &p_CFExpression, const QString &funct_params, QString *funct_local_vars)
{
    QString l_ElementName;
    QStringList strList;
	QString ret;
    bool close_funct = false;
    int c;

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
            throw QMKFusionTemplateException("Invalid boolean value.");
        }
        break;
    case Number:
        ret = l_ElementName;
        break;
    case String:
        if (p_CFExpression.m_ChildElements.size() == 1)
        {
            ret = GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements.first(), funct_params, funct_local_vars);
        }
        else if (p_CFExpression.m_ChildElements.size() > 0)
        {
            ret += '(';

            for(c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
            {
                if (c == 0)
                {
                    ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars);
                }
                else
                {
                    if (p_CFExpression.m_Type == String)
                    {
                        ret += " & " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars);
                    }
                    else
                    {
                        ret += " + " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars);
                    }
                }
            }

            ret += ')';
        }
        else
        {
            ret = "QString(\"" + toCPPEncodeStr(l_ElementName) + "\")";
        }
        break;
    case Variable:
        if (funct_local_vars)
        {
            ret = GenerateVariable(l_ElementName, funct_params, *funct_local_vars);
        }
        else
        {
            ret = GenerateVariable(l_ElementName, funct_params);
        }

        for (c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
        {
            ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars);
        }
        break;
    case VariableMember:
            if (p_CFExpression.m_ChildElements.count() == 1)
            {
                const QCFParserElement &item = p_CFExpression.m_ChildElements.first();

                if (item.m_Type == Variable)
                {
                    ret = "[L\"" + item.m_Text.toUpper() + "\"]";
                }
                else if (item.m_Type == String)
                {
                    ret = "[L\"" + item.m_Text + "\"]";
                }
                else if (item.m_Type == Number)
                {
                    ret = "[" + item.m_Text + "]";
                }
                else
                {
                    throw QMKFusionException("Unknown member access.");
                }
            }
            else if (p_CFExpression.m_ChildElements.count() > 1)
            {
                ret = "[" + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[0], funct_params, funct_local_vars) + "]";
            }
            else
            {
                throw QMKFusionException("Unknown member access.");
            }
        break;
    case Function:

        if (l_ElementName.toLower() == "isdefined")
            {
                ret = "cf_" + m_CFFunctionsDef[l_ElementName.toLower()].m_Name + "(p_TemplateInstance";

                for (c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
                {
                    ret += ", " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars);
                }
            } else {
                if (m_CFFunctionsDef.contains(l_ElementName.toLower()))
                {
                    ret = "cf_" + m_CFFunctionsDef[l_ElementName.toLower()].m_Name + "(";

                    for (c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
                    {
                        if (c > 0)
                        {
                            ret += ", ";
                        }
                        ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars);
                    }
                }
                else
                {
                    ret = "callCustomFunction(\"" + toCPPEncodeStr(l_ElementName.toLower()) + "\", QList<QWDDX>()";

                    for (c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
                    {
                        ret += " << " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars);
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
        else if (l_ElementName.compare(l_ElementName, "OR", Qt::CaseInsensitive) == 0)
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
        else if (l_ElementName == "[")
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
            ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars);
        }
        break;
    case Parameters:
        for (c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
        {
            if (c == 0)
            {
                ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars);
            }
            else
            {
                ret += ", " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars);
            }
        }
        break;
    case SharpExpression:
        ret = GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[0], funct_params, funct_local_vars);
        break;
    case Expression:
        c = 0;


        if (p_CFExpression.m_ChildElements.size() >= 2)
        {
            const QCFParserElement &var = p_CFExpression.m_ChildElements.at(0);
            const QCFParserElement &variable = p_CFExpression.m_ChildElements.at(1);

            if ((var.m_Type == Keyword)&&(var.m_Text.compare("var", Qt::CaseInsensitive) == 0)&&(variable.m_Type == Variable))
            {
                if (funct_local_vars)
                {
                    if (funct_local_vars->isEmpty())
                    {
                        *funct_local_vars = variable.m_Text.toUpper();
                    }
                    else
                    {
                        *funct_local_vars += "," + variable.m_Text.toUpper();
                    }
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
                    if(funct_local_vars)
                    {
                        localVars = funct_local_vars->split(',');
                    }

                    if (localVars.contains(destVar.m_Text.toUpper()))
                    {
                        ret += "updateVariable(LOCAL, QString(\"" + toCPPEncodeStr(destVar.m_Text.toUpper()) + "\"), ";
                    }
                    else
                    {
                        ret += "updateVariable(m_TemplateInstance->m_VARIABLES, QString(\"" + toCPPEncodeStr(destVar.m_Text.toUpper()) + "\"), ";
                    }
                }
                else if(destVar.m_ChildElements.count() > 0)
                {
                    QCFParserElement tmp = destVar;
                    QCFParserElement key = tmp.m_ChildElements.takeLast();

                    if ((key.m_ChildElements.count() == 1)&&(key.m_ChildElements.first().m_Type == Variable))
                    {
                        ret += "updateVariable(" + GenerateCFExpressionToCExpression(tmp, funct_params, funct_local_vars) + ", L\"" + key.m_ChildElements.first().m_Text.toUpper() + "\", ";
                    }
                    else
                    {
                        ret += "updateVariable(" + GenerateCFExpressionToCExpression(tmp, funct_params, funct_local_vars) + ", " + GenerateCFExpressionToCExpression(key.m_ChildElements.last(), funct_params, funct_local_vars) + ", ";
                    }
                }
                else
                {
                    return "";
                }

                close_funct = true;

                c = 2;
            }
            else
            {
                const QCFParserElement &op2 = p_CFExpression.m_ChildElements.at(2);

                if ((op2.m_Type == Operator)&&(op2.m_Text == "=")&&(p_CFExpression.m_ChildElements.first().m_Type == Keyword)&&(p_CFExpression.m_ChildElements.first().m_Text == "var"))
                {
                    const QCFParserElement &destVar = p_CFExpression.m_ChildElements.at(1);

                    if ((destVar.m_Type == Variable)&&(destVar.m_ChildElements.count() == 0))
                    {
                        ret += "updateVariable(LOCAL, QString(\"" + toCPPEncodeStr(destVar.m_Text.toUpper()) + "\"), ";
                    }
                    else if(destVar.m_ChildElements.count() > 0)
                    {
                        QCFParserElement tmp = destVar;
                        QCFParserElement key = tmp.m_ChildElements.takeLast();

                        if ((key.m_ChildElements.count() == 1)&&(key.m_ChildElements.first().m_Type == Variable))
                        {
                            ret += "updateVariable(" + GenerateCFExpressionToCExpression(tmp, funct_params, funct_local_vars) + ", L\"" + key.m_ChildElements.first().m_Text.toUpper() + "\", ";
                        }
                        else
                        {
                            ret += "updateVariable(" + GenerateCFExpressionToCExpression(tmp, funct_params, funct_local_vars) + ", " + GenerateCFExpressionToCExpression(key.m_ChildElements.last(), funct_params, funct_local_vars) + ", ";
                        }
                    }
                    else
                    {
                        return "";
                    }

                    close_funct = true;

                    c = 3;
                }
            }
        }

        for (; c < p_CFExpression.m_ChildElements.size(); c++)
        {
            ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], funct_params, funct_local_vars);
        }

        if (close_funct)
        {
            ret += ')';
        }

        break;
    case SubExpression:

        for (const QCFParserElement &expr : p_CFExpression.m_ChildElements)
        {
            strList << GenerateCFExpressionToCExpression(expr, funct_params, funct_local_vars);
        }

        ret.append("(" + strList.join(" ") + ")");
        break;

    case CodeBlock:

        ret += m_Tabs + " {\n";

        m_Tabs.append('\t');

        for (const QCFParserElement &expr : p_CFExpression.m_ChildElements)
        {
            ret += m_Tabs + GenerateCFExpressionToCExpression(expr, funct_params, funct_local_vars) + " ";

            if ((expr.m_Type == Expression)&&(expr.m_ChildElements.count() > 0))
            {
                if (expr.m_ChildElements.last().m_Type != CodeBlock)
                {
                    ret += ";";
                }
            }

            ret += "\n";
        }

        m_Tabs = m_Tabs.left(m_Tabs.length() - 1);

        ret += m_Tabs + "}\n";
        break;

    case Keyword:

        if (p_CFExpression.m_Text.compare("var", Qt::CaseInsensitive) != 0)
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

QString QCFGenerator::GenerateCodeFromString(const QString str)
{
    QCFParser parser;

    QCFParserElement l_newConditionElement = parser.ParseCFCode(str, (qint32)0, Expression, nullptr);

    return GenerateCFExpressionToCExpression(OptimizeQCFParserElement(l_newConditionElement));
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
				return GenerateCFExpressionToCExpression(l_Argument.m_ChildElements.at(2));
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
                    return GenerateCFExpressionToCExpression(l_Argument.m_ChildElements.at(2));
                }
            }

            break;
        }
    }

    throw QMKFusionTemplateException("Value is not string.");
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

    throw QMKFusionTemplateException("Value is not boolean.");
}

QString QCFGenerator::GenerateCCodeFromCFTag(const QCFParserTag &p_CFTag)
{
	if (p_CFTag.m_TagType == ExpressionTagType)
	{
        //return "f_WriteOutput(" + GenerateCFExpressionToCExpression(OprimizeQCFParserElement(p_CFTag.m_Arguments)) + ");";
        return m_Tabs + "f_WriteOutput(" + GenerateCFExpressionToCExpression(p_CFTag.m_Arguments) + ");";
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

    if(p_CFTag.m_Name.compare("cfabort", Qt::CaseInsensitive) == 0)
	{
		if (CFTagHasArgument(p_CFTag, "showError"))
		{
            return m_Tabs + "throw QMKFusionExpressionException(" + CFTagGetArgumentPlain(p_CFTag, "showError") + ");";
		}
		else
		{
            return m_Tabs + "throw QMKFusionCFAbortException();";
		}
	}
    else if(p_CFTag.m_Name.compare("cfapplication", Qt::CaseInsensitive) == 0)
    {
        bool has_name = CFTagHasArgument(p_CFTag, "name");

        if (has_name)
        {
            return m_Tabs + "f_Application(" + CFTagGetArgumentAsString(p_CFTag, "name") + ", " + CFTagGetArgumentAsBool(p_CFTag, "sessionmanagement") + ", " + CFTagGetArgumentAsBool(p_CFTag, "setclientcookies") + ");";
        }
        else
        {
            throw QMKFusionTemplateException(QString("cfapplication tag must have name attribute."));
        }
    }
    else if(p_CFTag.m_Name.compare("cfbreak", Qt::CaseInsensitive) == 0)
	{
        return m_Tabs + "break;";
	}
    else if(p_CFTag.m_Name.compare("cfcase", Qt::CaseInsensitive) == 0)
    {
        QString ret;

        if (p_CFTag.m_TagType == CFTagType)
        {
            if(m_SwitchCaseCount.last() > 0)
            {
                ret = m_Tabs + "else ";
            }

            m_SwitchCaseCount[m_SwitchCaseCount.count() - 1]++;

            QString switchValue = CFTagGetArgument(*m_SwitchTags.last(), "expression");
            QString caseValue = CFTagGetArgument(p_CFTag, "value");

            if (ret.isEmpty())
            {
                ret = m_Tabs + "if (" + switchValue + " == " + caseValue + ")\n";
            }
            else
            {
                ret += "if (" + switchValue + " == " + caseValue + ")\n";
            }

            ret += m_Tabs + "{\n";

            m_Tabs.append('\t');

            return ret;
        }
        else if (p_CFTag.m_TagType == EndCFTagType)
        {
            m_Tabs = m_Tabs.left(m_Tabs.length() - 1);

            return m_Tabs + "}\n";
        }
    }
    else if(p_CFTag.m_Name.compare("cfcatch", Qt::CaseInsensitive) == 0) /* NOT all types are implemented */
    {
        // TODO: NOT all cfcatch types are implemented.
        if (p_CFTag.m_TagType == CFTagType)
        {
            if (CFTagHasArgument(p_CFTag, "type"))
            {
                const QString &type = CFTagGetArgumentAsString(p_CFTag, "type").toLower();

                if (type == "application")
                {
                    return m_Tabs.left(m_Tabs.length() - 1) + "} catch(const QMKFusionApplicationException &ex) {";
                }
                else if(type == "database")
                {
                    return m_Tabs.left(m_Tabs.length() - 1) + "} catch(const QMKFusionDatabaseException &ex) {";
                }
                else if(type == "security")
                {
                    return m_Tabs.left(m_Tabs.length() - 1) + "} catch(const QMKFusionSecurityException &ex) {";
                }
                else if(type == "object")
                {
                    return m_Tabs.left(m_Tabs.length() - 1) + "} catch(const QMKFusionObjectException &ex) {";
                }
                else if(type == "missinginclude")
                {
                    return m_Tabs.left(m_Tabs.length() - 1) + "} catch(const QMKFusionMissingIncludeException &ex) {";
                }
                else if(type == "template")
                {
                    return m_Tabs.left(m_Tabs.length() - 1) + "} catch(const QMKFusionTemplateException &ex) {";
                }
                else if(type == "expression")
                {
                    return m_Tabs.left(m_Tabs.length() - 1) + "} catch(const QMKFusionExpressionException &ex) {";
                }
                else if(type == "lock")
                {
                    return m_Tabs.left(m_Tabs.length() - 1) + "} catch(const QMKFusionLockException &ex) {";
                }
                else if(type == "searchengine")
                {
                    return m_Tabs.left(m_Tabs.length() - 1) + "} catch(const QMKFusionSearchEngineException &ex) {";
                }
                else if(type == "any")
                {
                    return m_Tabs.left(m_Tabs.length() - 1) + "} catch(const QMKFusionException &ex) {";
                }
                else
                {
                    throw QMKFusionException(QString("Invalid cfcatch type[%1]").arg(type));
                }
            }

            return m_Tabs.left(m_Tabs.length() - 1) + "} catch(const QMKFusionException &ex) {";
        }
    }
    else if(p_CFTag.m_Name.compare("cfcookie", Qt::CaseInsensitive) == 0)
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

        return m_Tabs + "f_SetCookie(" + name + ", " + value + ", " + expires + ");\n";
    }
    else if(p_CFTag.m_Name.compare("cfdump", Qt::CaseInsensitive) == 0) /* Only 'var' parameter is implemented. */
	{
		if (p_CFTag.m_Arguments.m_Type != CFTagArguments)
		{
			return ""; //TODO: Generate Error.
		}

		if (p_CFTag.m_Arguments.m_ChildElements.size() != 1) // only var
		{
			return ""; //TODO: Generate Error.
		}

		if (p_CFTag.m_Arguments.m_ChildElements[0].m_ChildElements.size() != 3) // only var = "something"
		{
			return ""; //TODO: Generate Error.
		}

        return m_Tabs + "m_TemplateInstance->m_Output += mk_cfdump("+GenerateCFExpressionToCExpression(OptimizeQCFParserElement(p_CFTag.m_Arguments.m_ChildElements[0].m_ChildElements[2]))+");";
	}
    else if(p_CFTag.m_Name.compare("cffile", Qt::CaseInsensitive) == 0)
    {
        const QString &action = CFTagGetArgumentPlain(p_CFTag, "action").toLower();

        if (action == "delete")
        {
            const QString &file = CFTagGetArgument(p_CFTag, "file");

            return m_Tabs + "cf_FileDelete(\"" + toCPPEncodeStr(file) + "\");\n";
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
                throw QMKFusionException("At <cffile action=\"upload\" ... > destination parameter is empty or missing.");
            }
            destination = CFTagGetArgumentAsString(p_CFTag, "destination");

            if (!CFTagHasArgument(p_CFTag, "fileField"))
            {
                throw QMKFusionException("At <cffile action=\"upload\" ... > fileField parameter is empty or missing.");
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

            return m_Tabs + "f_FileUploadMove(" + destination + ", "  + fileField + ", " + accept + ", " + attributes + ", "  + mode + ", " + nameConflict + ", " + result + ");\n";
        }
    }
    else if(p_CFTag.m_Name.compare("cfinclude", Qt::CaseInsensitive) == 0)
    {
        return m_Tabs + "f_Include(" + CFTagGetArgument(p_CFTag, "template") + ");";
    }
    else if(p_CFTag.m_Name.compare("cfloop", Qt::CaseInsensitive) == 0) /* implemented: index, condition. missing: date or time, query, list or file or array, COM/DCOM collection or structure */
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
					l_Comparation = " >= ";
				}
				else
				{
					l_Comparation = " <= ";
				}

                if (CFTagHasArgument(p_CFTag, "step"))
                {
                    l_Step = CFTagGetArgument(p_CFTag, "step");
                }

				QCFParserElement l_Index = CFTagGetArgumentObject(p_CFTag, "index");
				QString l_IndexStr = l_Index.m_ChildElements[2].m_Text;

				if ((l_Index.m_Type != Error)&&(l_Index.m_ChildElements.size() == 3))
				{
                    ret  = m_Tabs + "for (f_Param(QString::fromWCharArray(L\"" + l_IndexStr + "\"), " + CFTagGetArgument(p_CFTag, "from") + "); (" + GenerateVariable(l_IndexStr) + ") " + l_Comparation + " (" + CFTagGetArgument(p_CFTag, "to") + "); " + GenerateVariable(l_IndexStr) + " = (" + GenerateVariable(l_IndexStr) + ").toNumber() + " + l_Step + ")\n";
                    ret += m_Tabs + "{\n";

                    m_Tabs.append('\t');

                    return ret;
				}
			}
			else if (CFTagHasArgument(p_CFTag, "condition"))
			{
                QCFParserElement l_conditionElement = CFTagGetArgumentObject(p_CFTag, "condition");

                if (l_conditionElement.m_ChildElements.count() == 3)
                {
                    QCFParser parser;

                    const QString &l_conditionStr = l_conditionElement.m_ChildElements.at(2).m_Text;

                    QCFParserElement l_newConditionElement = parser.ParseCFCode(l_conditionStr, (qint32)0, Expression, nullptr);

                    ret  = m_Tabs + "while(" + GenerateCFExpressionToCExpression(OptimizeQCFParserElement(l_newConditionElement)) + ")\n";
                    ret += m_Tabs + "{\n";

                    m_Tabs.append('\t');

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
                    ret = m_Tabs + "for(int i = " + start + "; i <= " + end + "; i++)\n";
                }
                else
                {
                    ret = m_Tabs + "for(int i = " + start + ";; i++)\n";
                }

                ret += m_Tabs + "{\n";

                m_Tabs.append('\t');

                ret += m_Tabs + "QWDDX l_Query(QWDDX::Struct);\n";
                ret += m_Tabs + "if (f_FetchQueryRow(l_Query, " + GenerateCodeFromString(CFTagGetArgumentPlain(p_CFTag, "query")) + ", i) == false) break;\n";
                ret += m_Tabs + "l_Query.m_HiddenScopeLast1 = m_TemplateInstance->m_VARIABLES.m_HiddenScopeFirst;\n";
                ret += m_Tabs + "m_TemplateInstance->m_VARIABLES.m_HiddenScopeFirst = &l_Query;\n";

                return ret;
            }
        }

		if (p_CFTag.m_TagType == EndCFTagType)
		{
            if (CFTagHasArgument(*p_CFTag.m_OtherTag, "query"))
            {
                ret += m_Tabs + "m_TemplateInstance->m_VARIABLES.m_HiddenScopeFirst = l_Query.m_HiddenScopeLast1;\n";
            }

            m_Tabs = m_Tabs.left(m_Tabs.length() - 1);

            ret += m_Tabs + "}";

            return ret;
		}
	}
    else if(p_CFTag.m_Name.compare("cfset", Qt::CaseInsensitive) == 0)
	{
        QCFParserElement l_OptimizedElements = OptimizeQCFParserElement(p_CFTag.m_Arguments);
		//QCFParserElement l_OptimizedElements = p_CFTag.m_Arguments;

//		log("m_ChildElements.size() = " + QString::number(l_OptimizedElements.m_ChildElements.size()));

        // FIXME: Same code in both branches.
		if ((l_OptimizedElements.m_ChildElements.size() > 1)&&(l_OptimizedElements.m_ChildElements[0].m_Type == Variable)&&(l_OptimizedElements.m_ChildElements[1].m_Type == Operator)&&(l_OptimizedElements.m_ChildElements[1].m_Text == "="))
		{
            return m_Tabs + GenerateCFExpressionToCExpression(l_OptimizedElements) + ";";
		}
		else
		{
            return m_Tabs + GenerateCFExpressionToCExpression(l_OptimizedElements) + ";";
		}
	}
    else if(p_CFTag.m_Name.compare("cfoutput", Qt::CaseInsensitive) == 0)
	{
        QString ret;

		if (p_CFTag.m_TagType == CFTagType)
		{
            ret += m_Tabs + "p_TemplateInstance->m_CFOutput++;\n";

            if (CFTagHasArgument(p_CFTag, "query"))
            {
                ret += m_Tabs + "for(int i = 1; ; i++)\n";
                ret += m_Tabs + "{\n";

                m_Tabs.append('\t');

                ret += m_Tabs + "QWDDX l_Query(QWDDX::Struct);\n";
                ret += m_Tabs + "if (f_FetchQueryRow(l_Query, " + GenerateCodeFromString(CFTagGetArgumentPlain(p_CFTag, "query")) + ", i) == false) break;\n";
                ret += m_Tabs + "l_Query.m_HiddenScopeLast1 = m_TemplateInstance->m_VARIABLES.m_HiddenScopeFirst;\n";
                ret += m_Tabs + "m_TemplateInstance->m_VARIABLES.m_HiddenScopeFirst = &l_Query;\n";
            }

            return ret;
		}

		if (p_CFTag.m_TagType == EndCFTagType)
		{
            if (CFTagHasArgument(*p_CFTag.m_OtherTag, "query"))
            {
                ret += m_Tabs + "m_TemplateInstance->m_VARIABLES.m_HiddenScopeFirst = l_Query.m_HiddenScopeLast1;\n";

                m_Tabs = m_Tabs.left(m_Tabs.length() - 1);

                ret += m_Tabs + "}\n";
            }

            ret += m_Tabs + "p_TemplateInstance->m_CFOutput--;\n";

            return ret;
		}
	}
    else if(p_CFTag.m_Name.compare("cfparam", Qt::CaseInsensitive) == 0) /*cfparam "name type" is missing */
    {
        bool has_name = CFTagHasArgument(p_CFTag, "name");
        bool has_default = CFTagHasArgument(p_CFTag, "default");
        bool has_type = CFTagHasArgument(p_CFTag, "type");

        if ((has_name)&&(has_default))
        {
            return m_Tabs + "f_Param(" + CFTagGetArgument(p_CFTag, "name") + ", " + CFTagGetArgument(p_CFTag, "default") + ");";
        }
        else if ((has_name)&&(!has_type))
        {
            return m_Tabs + "f_Param(" + CFTagGetArgument(p_CFTag, "name") + ");";
        }
        else if ((has_name)&&(has_type))
        {
            return m_Tabs + "unimplemented()";
        }
        else
        {
            return m_Tabs + "parser error()";
        }
    }
    else if(p_CFTag.m_Name.compare("cfreturn", Qt::CaseInsensitive) == 0)
    {
        QCFParserElement l_OptimizedElements = OptimizeQCFParserElement(p_CFTag.m_Arguments);

        return m_Tabs + "return " + GenerateCFExpressionToCExpression(l_OptimizedElements) + ";";
    }
    else if(p_CFTag.m_Name.compare("cfif", Qt::CaseInsensitive) == 0)
	{
		if (p_CFTag.m_TagType == CFTagType)
		{
            QString ret;

            //return "if (" + GenerateCFExpressionToCExpression(OprimizeQCFParserElement(p_CFTag.m_Arguments)) + ") {";
            ret  = m_Tabs + "if (" + GenerateCFExpressionToCExpression(p_CFTag.m_Arguments) + ")\n";
            ret += m_Tabs + "{\n";

            m_Tabs.append('\t');

            return ret;
		}
		if (p_CFTag.m_TagType == EndCFTagType)
		{
            m_Tabs = m_Tabs.left(m_Tabs.length() - 1);

            return m_Tabs + "}";
		}
	}
    else if(p_CFTag.m_Name.compare("cfelse", Qt::CaseInsensitive) == 0)
	{
		if (p_CFTag.m_TagType == CFTagType)
		{
            return m_Tabs.left(m_Tabs.length() - 1) + "} else {";
		}
	}
    else if(p_CFTag.m_Name.compare("cfelseif", Qt::CaseInsensitive) == 0)
	{
		if (p_CFTag.m_TagType == CFTagType)
		{
			//return "} else if(" + GenerateCFExpressionToCExpression(OprimizeQCFParserElement(p_CFTag.m_Arguments)) + ") {";
            return m_Tabs.left(m_Tabs.length() - 1) + "} else if(" + GenerateCFExpressionToCExpression(p_CFTag.m_Arguments) + ") {";
		}
	}
    else if(p_CFTag.m_Name.compare("cflocation", Qt::CaseInsensitive) == 0)
    {
        if (!CFTagHasArgument(p_CFTag, "url"))
        {
            throw QMKFusionTemplateException("cflocation tag must have url attribute.");
        }

        if ((!CFTagHasArgument(p_CFTag, "addToken"))&&(!CFTagHasArgument(p_CFTag, "statusCode")))
        {
            return m_Tabs + "f_Location(" + CFTagGetArgument(p_CFTag, "url") + ");\n";
        }
        else if ((CFTagHasArgument(p_CFTag, "addToken"))&&(!CFTagHasArgument(p_CFTag, "statusCode")))
        {
            throw QMKFusionTemplateException("cflocation url addToken is NOT implemented.");
        }
        else if ((!CFTagHasArgument(p_CFTag, "addToken"))&&(CFTagHasArgument(p_CFTag, "statusCode")))
        {
            throw QMKFusionTemplateException("cflocation url, statusCode is NOT implemented.");
        }
        else
        {
            throw QMKFusionTemplateException("cflocation url, addToken, statusCode is NOT implemented.");
        }
    }
    else if(p_CFTag.m_Name.compare("cfsetting", Qt::CaseInsensitive) == 0) /* implemented attributes: enablecfoutputonly. */
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
    else if(p_CFTag.m_Name.compare("cfswitch", Qt::CaseInsensitive) == 0)
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
    else if(p_CFTag.m_Name.compare("cftry", Qt::CaseInsensitive) == 0)
    {
        QString ret;

        if (p_CFTag.m_TagType == CFTagType)
        {
            ret = m_Tabs + "try {";

            m_Tabs.append('\t');

            return ret;
        }
        else
        {
            m_Tabs = m_Tabs.left(m_Tabs.length() - 1);

            return m_Tabs + "}";
        }
    }
    else if(p_CFTag.m_Name.compare("cfquery", Qt::CaseInsensitive) == 0) /* implemented attributes: name, datasource. */
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
                return m_Tabs + "startQuery();";
            }

            if (p_CFTag.m_TagType == EndCFTagType)
            {
                // TODO: LOCAL is missing.
                return m_Tabs + "updateVariable(m_TemplateInstance->m_VARIABLES, L\"" + l_queryName.toUpper() + "\", endQuery(" + l_queryDataSource + "));";
            }
        }
        else if (((l_queryType.isEmpty())||(l_queryType.compare("query", Qt::CaseInsensitive) == 0))&&(l_queryName.isEmpty())&&(!l_queryDataSource.isEmpty()))
        {
            if (p_CFTag.m_TagType == CFTagType)
            {
                return m_Tabs + "startQuery();";
            }

            if (p_CFTag.m_TagType == EndCFTagType)
            {
                return m_Tabs + "endQueryNoReturn(" + l_queryDataSource + ");";
            }
        }
    }
    else if(p_CFTag.m_Name.compare("cfqueryparam", Qt::CaseInsensitive) == 0) /* implemented attributes: value. */
    {
        if (p_CFTag.m_TagType == CFTagType)
        {
            return m_Tabs + "m_TemplateInstance->m_QueryParams.append(" +  CFTagGetArgument(p_CFTag, "value") + "); f_WriteOutput(QString::fromWCharArray(L\"?\", 1));";
        }
    }

    return "";
}
