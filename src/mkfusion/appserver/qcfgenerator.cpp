#include "qcfgenerator.h"
#include "qcfserver.h"
#include "qcfparser.h"
#include "qcf8.h"

#include <QDateTime>
#include <QProcess>
#include <QList>
#include <QDir>


QString toCPPEncodeStr(const QString &str)
{
	QString ret;

	for(int c = 0; c < str.length(); c++)
	{

		ushort ch = str[c].unicode();

		switch(ch)
		{
		case '\0':
			ret += "\\0";
			continue;
			break;
		case '\\':
			ret += "\\\\";
			continue;
			break;
		case '\'':
			ret += "\\\'";
			continue;
			break;
		case '\"':
			ret += "\\\"";
			continue;
			break;
		case '\n':
			ret += "\\n";
			continue;
			break;
		case '\r':
			ret += "\\r";
			continue;
			break;
		case '\t':
			ret += "\\t";
			continue;
			break;
		}

		if ((str[c].unicode() >= 32)&&(str[c].unicode() <= 128))
		{
			ret += str[c];
			continue;
		}

		QString tmp = QString::number(str[c].unicode(), 16);

		for(; ; )
		{
			if (tmp.length() >= 4)
			{
				break;
			}

			tmp = '0' + tmp;
		}
		ret += "\\x" + tmp;
	}

	return ret;
}

QCFGenerator::QCFGenerator()
{
	m_CFTagsDef = QCF8::generateCFTags();
	m_CFFunctionsDef = QCF8::generateCFFunctions();
	m_EnableCFOutputOnly = false;
	m_Tabs = 2;
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
	l_cppFile.write("	}\n");
	l_cppFile.write("	\n");
    l_cppFile.write("	virtual void run(QCFRunningTemplate *p_TemplateInstance)\n");
	l_cppFile.write("	{\n"); // mybase::myfunc() ;
	l_cppFile.write("		QCFTemplate::run(p_TemplateInstance);\n");

	QList<QCFParserTag> const l_Tags = p_Parser.getTags();
	QString l_Text = p_Parser.getText();
	QString l_tmpStr;
	QString line = "\t\t";

	qint32 l_CFCodeInsideTags = 0;

	for(int c = 0; c < l_Tags.size(); c++)
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
                    l_cppFile.write(QString(line + "f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
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
                    l_cppFile.write(QString(line + "f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
				}
			}
		}

		QString l_CFromCFTag = GenerateCCodeFromCFTag(l_Tags[c]);
		if (!l_CFromCFTag.isEmpty())
		{
            l_cppFile.write(QString("\n// Line %1.\n").arg(l_Tags[c].m_Start).toUtf8());
            l_cppFile.write(QString(line + l_CFromCFTag + "\n").toUtf8());
		}

		if ((l_cf8tags.contains(l_Tags[c].m_Name))&&(l_cf8tags[l_Tags[c].m_Name].m_ExpressionInside == QCFTag::WithExpressionInside))
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
            l_cppFile.write(QString(line + "f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
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
                l_cppFile.write(QString(line + "f_WriteOutput(QString::fromWCharArray(L\"" + toCPPEncodeStr(l_tmpStr) + "\", " + QString::number(l_tmpStr.length()) + "));\n").toUtf8());
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
    process.start("g++ -c -pipe -O2 -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_NO_DEBUG -DQT_CORE_LIB -DQT_SHARED -I/usr/share/qt5/mkspecs/linux-g++ -I. -I/usr/include/qt5/QtCore -I/usr/include/qt5/QtNetwork -I/usr/include/qt5/QtConcurrent -I/usr/include/qt5 -I\""+p_MKFusionPath+"include\" -o \""+p_MKFusionPath+"templates/"+l_NewTarget+".o\" \""+p_MKFusionPath+"templates/"+l_NewTarget+".cpp\"");
#else
    process.start("g++ -c -pipe -g -std=c++0x -Wall -W -D_REENTRANT -fPIE -DQT_CORE_LIB -DQT_SHARED -I/usr/share/qt5/mkspecs/linux-g++ -I. -I/usr/include/qt5/QtCore -I/usr/include/qt5/QtNetwork -I/usr/include/qt5/QtConcurrent -I/usr/include/qt5 -I\""+p_MKFusionPath+"include\" -o \""+p_MKFusionPath+"templates/"+l_NewTarget+".o\" \""+p_MKFusionPath+"templates/"+l_NewTarget+".cpp\"");
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
    process.start("g++ -Wl,-O1 -shared -o \""+p_MKFusionPath+"templates/"+l_NewTarget+".so\" \""+p_MKFusionPath+"templates/"+l_NewTarget+".o\" -L/usr/lib/x86_64-linux-gnu -lQt5Concurrent -lrt -lQt5Core -lpthread");
#else
    process.start("g++ -shared -o \""+p_MKFusionPath+"templates/"+l_NewTarget+".so\" \""+p_MKFusionPath+"templates/"+l_NewTarget+".o\" -L/usr/lib/x86_64-linux-gnu -lQt5Concurrent -lrt -lQt5Core -lpthread");
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

QString QCFGenerator::GenerateVariable(const QString &p_Variable)
{
	QString ret;
	QString l_Variable = p_Variable;

	if (
		   (l_Variable.startsWith("CGI.", Qt::CaseInsensitive) == 0) \
		&& (l_Variable.compare("CGI", Qt::CaseInsensitive) != 0) \
		&& (l_Variable.startsWith("SERVER.", Qt::CaseInsensitive) == 0) \
		&& (l_Variable.compare("SERVER", Qt::CaseInsensitive) != 0) \
		&& (l_Variable.startsWith("URL.", Qt::CaseInsensitive) == 0) \
		&& (l_Variable.compare("URL", Qt::CaseInsensitive) != 0) \
		&& (l_Variable.startsWith("POST.", Qt::CaseInsensitive) == 0) \
		&& (l_Variable.compare("POST", Qt::CaseInsensitive) != 0) \
		&& (l_Variable.startsWith("VARIABLES.", Qt::CaseInsensitive) == 0) \
		&& (l_Variable.compare("VARIABLES", Qt::CaseInsensitive) != 0) \
	   )
	{
		l_Variable = "VARIABLES." + l_Variable;
	}

	QStringList l_StrList = l_Variable.split(".");

	if (l_StrList.size() < 1)
	{
		return "";
	}

	ret = "m_TemplateInstance->m_" + l_StrList[0].toUpper();

	for(int c = 1; c < l_StrList.size(); c++)
	{
        ret += "[\""+l_StrList[c].toUpper()+"\"]";
	}

	return ret;
}

QString QCFGenerator::GenerateCFExpressionToCExpression(const QCFParserElement &p_CFExpression)
{
	QString ret;
	QString l_ElementName = p_CFExpression.m_Text;

	switch(p_CFExpression.m_Type)
	{
		case Boolean:
			ret = "QWDDX(" + l_ElementName.toLower() + ")";
			break;
		case Number:
			ret = "QWDDX(" + l_ElementName + ")";
			break;
		case String:
			if (p_CFExpression.m_ChildElements.size() == 1)
			{
				ret = GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[0]);
			}
			else if (p_CFExpression.m_ChildElements.size() > 0)
			{
				for(int c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
				{
					if (c == 0)
					{
						ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c]);
					}
					else
					{
                        if (p_CFExpression.m_Type == String)
                        {
                            ret += " & " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c]);
                        }
                        else
                        {
                            ret += " + " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c]);
                        }
					}
				}
			}
			else
			{
                ret = "\"" + l_ElementName + "\""; // TODO: Currently this line will always convert Utf8 to Unicode.
			}
			break;
		case Variable:
			ret = GenerateVariable(l_ElementName);
			for (int c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
			{
				ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c]);
			}
			break;
		case VariableIndex:
				if (p_CFExpression.m_ChildElements.count() > 0)
				{
					ret = "[" + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[0]) + "]";
				}
			break;
		case Function:

            if (l_ElementName.toLower() == "isdefined")
                {
                    ret = "cf_" + m_CFFunctionsDef[l_ElementName.toLower()].m_Name + "(p_TemplateInstance";

                    for (int c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
                    {
                        ret += ", " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c]);
                    }
                } else {
                    ret = "cf_" + m_CFFunctionsDef[l_ElementName.toLower()].m_Name + "(";

                    for (int c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
                    {
                        if (c > 0)
                        {
                            ret += ", ";
                        }
                        ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c]);
                    }
                }

				ret += ")";
			break;
		case Operator:
			if (l_ElementName.compare(l_ElementName, "eq", Qt::CaseInsensitive) == 0)
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
			else if (l_ElementName.compare(l_ElementName, "AND", Qt::CaseInsensitive) == 0)
			{
				ret = " && ";
			}
			else if (l_ElementName.compare(l_ElementName, "OR", Qt::CaseInsensitive) == 0)
			{
				ret = " || ";
			}
			else if (l_ElementName.compare(l_ElementName, "NOT", Qt::CaseInsensitive) == 0)
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
            else if (l_ElementName.compare("MOD", Qt::CaseInsensitive) == 0)
			{
                ret = " % ";
			}
			else
			{
				ret = " " + l_ElementName + " ";
			}
			break;
		case Parameter:
			for (int c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
			{
				ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c]);
			}
			break;
		case Parameters:
			for (int c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
			{
				if (c == 0)
				{
					ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c]);
				}
				else
				{
					ret += ", " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c]);
				}
			}

			break;
		case SharpExpression:
            ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[0]);
        break;
		case Expression:
			for (int c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
			{
				ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c]);
			}

			break;
		case SubExpression:
			ret += "( ";

			for (int c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
			{
				ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c]) + " ";
			}

			ret += ")";
		default:;
			break;
	}

	return ret;
}

QCFParserElement QCFGenerator::OprimizeQCFParserElement(QCFParserElement p_CFExpression)
{
	for(int c = 0; c < p_CFExpression.m_ChildElements.count(); c++)
	{
		p_CFExpression.m_ChildElements[c] = OprimizeQCFParserElement(p_CFExpression.m_ChildElements[c]);
	}

	if ((p_CFExpression.m_ChildElements.length() == 1)&&((p_CFExpression.m_Type == Expression)||(p_CFExpression.m_Type == SharpExpression)||(p_CFExpression.m_Type == Parameters)||(p_CFExpression.m_Type == Parameter)))// TODO: Maybe add another types
	{
		return p_CFExpression.m_ChildElements[0];
	}

	return p_CFExpression;
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

QString QCFGenerator::GenerateCCodeFromCFTag(const QCFParserTag &p_CFTag)
{
	if (p_CFTag.m_TagType == ExpressionTagType)
	{
		//return "f_WriteOutput(" + GenerateCFExpressionToCExpression(OprimizeQCFParserElement(p_CFTag.m_Arguments)) + ");";
		return "f_WriteOutput(" + GenerateCFExpressionToCExpression(p_CFTag.m_Arguments) + ");";
	}

    if(p_CFTag.m_Name.compare("cfabort", Qt::CaseInsensitive) == 0)
	{
		if (CFTagHasArgument(p_CFTag, "showError"))
		{
            return "throw QMKFusionExpressionException(" + CFTagGetArgumentPlain(p_CFTag, "showError") + ");";
		}
		else
		{
			return "throw QMKFusionCFAbortException();";
		}
	}
    else if(p_CFTag.m_Name.compare("cfbreak", Qt::CaseInsensitive) == 0)
	{
		return "break;";
	}
    else if(p_CFTag.m_Name.compare("cfcatch", Qt::CaseInsensitive) == 0) /* type parameter is NOT implemented */
    {
        // TODO: implement try-catch type.
        if (p_CFTag.m_TagType == CFTagType)
        {
            return "} catch(const QMKFusionException &ex) {";
        }
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

		return "f_WriteOutput(mk_cfdump("+GenerateCFExpressionToCExpression(OprimizeQCFParserElement(p_CFTag.m_Arguments.m_ChildElements[0].m_ChildElements[2]))+"));";
		//return "f_WriteOutput(mk_cfdump("+GenerateCFExpressionToCExpression(p_CFTag.m_Arguments.m_ChildElements[0].m_ChildElements[2], "false")+"));";
	}
    else if(p_CFTag.m_Name.compare("cfloop", Qt::CaseInsensitive) == 0) /* implemented: index, condition. missing: date or time, query, list or file or array, COM/DCOM collection or structure */
	{
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
                    return "for (" + GenerateVariable(l_IndexStr) + " = (" + CFTagGetArgument(p_CFTag, "from") + ").toNumber(); (" + GenerateVariable(l_IndexStr) + ").toNumber() " + l_Comparation + " (" + CFTagGetArgument(p_CFTag, "to") + ").toNumber(); " + GenerateVariable(l_IndexStr) + " = (" + GenerateVariable(l_IndexStr) + ").toNumber() + " + l_Step + ") {";
				}
			}
			else if (CFTagHasArgument(p_CFTag, "condition"))
			{
                QCFParserElement l_conditionElement = CFTagGetArgumentObject(p_CFTag, "condition");

                if (l_conditionElement.m_ChildElements.count() == 3)
                {
                    QCFParser parser;

                    const QString &l_conditionStr = l_conditionElement.m_ChildElements.at(2).m_Text;

                    QCFParserElement l_newConditionElement = parser.ParseCFCode(l_conditionStr, (qint32)0, Expression, NULL);

                    return "while(" + GenerateCFExpressionToCExpression(OprimizeQCFParserElement(l_newConditionElement)) + ") {";
                }

                // TODO: Generate Error.
			}
		}

		if (p_CFTag.m_TagType == EndCFTagType)
		{
			return "}";
		}
	}
    else if(p_CFTag.m_Name.compare("cfset", Qt::CaseInsensitive) == 0)
	{
		QCFParserElement l_OptimizedElements = OprimizeQCFParserElement(p_CFTag.m_Arguments);
		//QCFParserElement l_OptimizedElements = p_CFTag.m_Arguments;

//		log("m_ChildElements.size() = " + QString::number(l_OptimizedElements.m_ChildElements.size()));

		if ((l_OptimizedElements.m_ChildElements.size() > 1)&&(l_OptimizedElements.m_ChildElements[0].m_Type == Variable)&&(l_OptimizedElements.m_ChildElements[1].m_Type == Operator)&&(l_OptimizedElements.m_ChildElements[1].m_Text == "="))
		{
			return GenerateCFExpressionToCExpression(l_OptimizedElements) + ";";
		}
		else
		{
			return GenerateCFExpressionToCExpression(l_OptimizedElements) + ";";
		}
	}
    else if(p_CFTag.m_Name.compare("cfoutput", Qt::CaseInsensitive) == 0)
	{
		if (p_CFTag.m_TagType == CFTagType)
		{
			return "p_TemplateInstance->m_CFOutput++;";
		}

		if (p_CFTag.m_TagType == EndCFTagType)
		{
			return "p_TemplateInstance->m_CFOutput--;";
		}
	}
    else if(p_CFTag.m_Name.compare("cfif", Qt::CaseInsensitive) == 0)
	{
		if (p_CFTag.m_TagType == CFTagType)
		{
			//return "if (" + GenerateCFExpressionToCExpression(OprimizeQCFParserElement(p_CFTag.m_Arguments)) + ") {";
			return "if (" + GenerateCFExpressionToCExpression(p_CFTag.m_Arguments) + ") {";
		}
		if (p_CFTag.m_TagType == EndCFTagType)
		{
			return "}";
		}
	}
    else if(p_CFTag.m_Name.compare("cfelse", Qt::CaseInsensitive) == 0)
	{
		if (p_CFTag.m_TagType == CFTagType)
		{
			return "} else {";
		}
	}
    else if(p_CFTag.m_Name.compare("cfelseif", Qt::CaseInsensitive) == 0)
	{
		if (p_CFTag.m_TagType == CFTagType)
		{
			//return "} else if(" + GenerateCFExpressionToCExpression(OprimizeQCFParserElement(p_CFTag.m_Arguments)) + ") {";
			return "} else if(" + GenerateCFExpressionToCExpression(p_CFTag.m_Arguments) + ") {";
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
    else if(p_CFTag.m_Name.compare("cftry", Qt::CaseInsensitive) == 0)
    {
        if (p_CFTag.m_TagType == CFTagType)
        {
            return "try {";
        }
        else
        {
            return "}";
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
                l_queryDataSource = CFTagGetArgumentPlain(p_CFTag, "datasource");
                break;
            case EndCFTagType:
                l_queryType = CFTagGetArgumentPlain(*p_CFTag.m_OtherTag, "type");
                l_queryName = CFTagGetArgumentPlain(*p_CFTag.m_OtherTag, "name");
                l_queryDataSource = CFTagGetArgumentPlain(*p_CFTag.m_OtherTag, "datasource");
                break;
            default:
                break;
        }

        if (((l_queryType.isEmpty())||(l_queryType.compare("query", Qt::CaseInsensitive) == 0))&&(!l_queryName.isEmpty())&&(!l_queryDataSource.isEmpty()))
        {
            if (p_CFTag.m_TagType == CFTagType)
            {
                return "startQuery();";
            }

            if (p_CFTag.m_TagType == EndCFTagType)
            {
                return "m_TemplateInstance->m_VARIABLES[\"" + l_queryName.toUpper() + "\"] = endQuery(\"" + l_queryDataSource + "\");";
            }
        }
    }
    else if(p_CFTag.m_Name.compare("cfqueryparam", Qt::CaseInsensitive) == 0) /* implemented attributes: value. */
    {
        if (p_CFTag.m_TagType == CFTagType)
        {
            return "m_TemplateInstance->m_QueryParams.append(" +  CFTagGetArgument(p_CFTag, "value") + "); f_WriteOutput(QString::fromWCharArray(L\"?\", 1));";
        }
    }

	return "";
}
