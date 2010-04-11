#include "qcfgenerator.h"
#include "qcfserver.h"
#include "qcfparser.h"
#include "qcf8.h"

#include <QDateTime>
#include <QProcess>
#include <QList>
#include <QDir>

#ifdef Q_WS_WIN

#include <windows.h>


#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

QString getQtDir()
{
	HKEY reg, reg2;
	QString key = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", subkey;
	QString tempQSt;
	WCHAR temp[MAX_KEY_LENGTH];
	DWORD valstrsize = MAX_KEY_LENGTH;
	DWORD valType;
	DWORD dwordVal;

	QString retQtSDK, retQtOpenSource;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, key.toStdWString().c_str(), 0, KEY_ENUMERATE_SUB_KEYS, &reg) == ERROR_SUCCESS)
	{

		for(quint32 c = 0; ; c++)
		{
			if (RegEnumKey(reg, c, temp, MAX_KEY_LENGTH) != ERROR_SUCCESS)
			{
				break;
			}

			subkey = QString::fromStdWString(temp);

			if (subkey.startsWith("Qt SDK "))
			{
				if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, key.append("\\"+subkey).toStdWString().c_str(), 0, KEY_QUERY_VALUE, &reg2) == ERROR_SUCCESS)
				{

					valstrsize = MAX_KEY_LENGTH;
					if (RegQueryValueEx(reg2, L"QtInstalled", NULL, &valType, (BYTE*)&dwordVal, &valstrsize) == ERROR_SUCCESS)
					{
						if (dwordVal == 1)
						{
							valstrsize = MAX_KEY_LENGTH;
							if (RegQueryValueEx(reg2, L"QTSDK_INSTDIR", NULL, &valType, (BYTE*)temp, &valstrsize) == ERROR_SUCCESS)
							{
								retQtSDK = QString::fromStdWString(temp) + "\\qt\\";
							}
						}
					}

					RegCloseKey(reg2);
				}
			}

			if (subkey.startsWith("Qt OpenSource "))
			{
				if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, key.append("\\"+subkey).toStdWString().c_str(), 0, KEY_QUERY_VALUE, &reg2) == ERROR_SUCCESS)
				{
					valstrsize = MAX_KEY_LENGTH;
					if (RegQueryValueEx(reg2, L"QTSDK_INSTDIR", NULL, &valType, (BYTE*)temp, &valstrsize) == ERROR_SUCCESS)
					{
						retQtOpenSource = QString::fromStdWString(temp) + '\\';
					}
					else
					{
						valstrsize = MAX_KEY_LENGTH;
						if (RegQueryValueEx(reg2, L"MINGW_INSTDIR", NULL, &valType, (BYTE*)temp, &valstrsize) == ERROR_SUCCESS)
						{
							retQtOpenSource = QString::fromStdWString(temp) + '\\';
						}
					}

					RegCloseKey(reg2);
				}
			}
		}

		RegCloseKey(reg);
	}

	if (!retQtSDK.isEmpty())
	{
		return retQtSDK;
	}

	if (!retQtOpenSource.isEmpty())
	{
		return retQtOpenSource;
	}

	return "";
}

QString getMingwDir()
{
	HKEY reg, reg2;
	QString key = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", subkey;
	QString tempQSt;
	WCHAR temp[MAX_KEY_LENGTH];
	DWORD valstrsize = MAX_KEY_LENGTH;
	DWORD valType;
	DWORD dwordVal;

	QString retQtSDK, retQtOpenSource, retMingw;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, key.toStdWString().c_str(), 0, KEY_ENUMERATE_SUB_KEYS, &reg) == ERROR_SUCCESS)
	{

		for(quint32 c = 0; ; c++)
		{
			if (RegEnumKey(reg, c, temp, MAX_KEY_LENGTH) != ERROR_SUCCESS)
			{
				break;
			}

			subkey = QString::fromStdWString(temp);

			if (subkey.startsWith("Qt SDK "))
			{
				if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, key.append("\\"+subkey).toStdWString().c_str(), 0, KEY_QUERY_VALUE, &reg2) == ERROR_SUCCESS)
				{
					valstrsize = MAX_KEY_LENGTH;
					if (RegQueryValueEx(reg2, L"MinGWInstalled", NULL, &valType, (BYTE*)&dwordVal, &valstrsize) == ERROR_SUCCESS)
					{
						if (dwordVal == 1)
						{
							valstrsize = MAX_KEY_LENGTH;
							if (RegQueryValueEx(reg2, L"QTSDK_INSTDIR", NULL, &valType, (BYTE*)temp, &valstrsize) == ERROR_SUCCESS)
							{
								retQtSDK = QString::fromStdWString(temp) + "\\mingw\\";
							}
						}
					}

					RegCloseKey(reg2);
				}
			}

			if (subkey.startsWith("Qt OpenSource "))
			{
				if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, key.append("\\"+subkey).toStdWString().c_str(), 0, KEY_QUERY_VALUE, &reg2) == ERROR_SUCCESS)
				{
					valstrsize = MAX_KEY_LENGTH;
					if (RegQueryValueEx(reg2, L"MINGWInstalled", NULL, &valType, (BYTE*)&dwordVal, &valstrsize) == ERROR_SUCCESS)
					{
						if (dwordVal == 1)
						{
							valstrsize = MAX_KEY_LENGTH;
							if (RegQueryValueEx(reg2, L"MinGWInstDir", NULL, &valType, (BYTE*)temp, &valstrsize) == ERROR_SUCCESS)
							{
								retQtOpenSource = QString::fromStdWString(temp) + "\\";
							}
						}
					}

					RegCloseKey(reg2);
				}
			}

			if (subkey.startsWith("MinGW "))
			{
				if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, key.append("\\"+subkey).toStdWString().c_str(), 0, KEY_QUERY_VALUE, &reg2) == ERROR_SUCCESS)
				{
					valstrsize = MAX_KEY_LENGTH;
					if (RegQueryValueEx(reg2, L"UninstallString", NULL, &valType, (BYTE*)temp, &valstrsize) == ERROR_SUCCESS)
					{
						retMingw = QString::fromStdWString(temp);
						if (retMingw.endsWith("\\uninst.exe"))
						{
							retMingw = retMingw.left(retMingw.length() - 10);
						}
						else
						{
							retMingw = "";
						}
					}

					RegCloseKey(reg2);
				}
			}
		}

		RegCloseKey(reg);
	}

	if (!retQtSDK.isEmpty())
	{
		return retQtSDK;
	}

	if (!retQtOpenSource.isEmpty())
	{
		return retQtOpenSource;
	}

	if (!retMingw.isEmpty())
	{
		return retMingw;
	}

	return "";
}
#endif

bool RemoveDirectory(QDir aDir)
{
	bool has_err = false;
	if (aDir.exists())
	{
		QFileInfoList entries = aDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
		int count = entries.size();
		for (int idx = 0; ((idx < count) && (has_err == false)); idx++)
		{
			QFileInfo entryInfo = entries[idx];
			QString path = entryInfo.absoluteFilePath();
			if (entryInfo.isDir())
			{
				has_err = RemoveDirectory(QDir(path));
			}
			else
			{
				QFile file(path);
				if (!file.remove())
				has_err = true;
			}
		}
		if (!aDir.rmdir(aDir.absolutePath()))
		has_err = true;
	}
	return(has_err);
}

QString toCPPEncodeStr(const QString& str)
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
}


QString QCFGenerator::compile(QCFParser& p_Parser, const QString& p_Target, const QString& p_MKFusionPath)
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
	l_cppFile.write("#ifdef Q_WS_WIN\n");
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
	l_cppFile.write(("		m_isModified.m_Filename = QString::fromWCharArray(L\"" + toCPPEncodeStr(p_Parser.m_FileName) + "\");\n").toAscii());
	l_cppFile.write(("		m_isModified.m_Size = " + QString::number(p_Parser.m_CFMFileSize) + ";\n").toAscii());
	l_cppFile.write(("		m_isModified.m_Modified = " + QString::number(p_Parser.m_CFMModifyDateTime) + ";\n").toAscii());
	l_cppFile.write("	}\n");
	l_cppFile.write("	\n");
	l_cppFile.write("	virtual void run(QCFRunningTemplate* p_TemplateInstance)\n");
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

				l_cppFile.write((line+"f_WriteOutput(QString::fromWCharArray(L\""+toCPPEncodeStr(l_tmpStr)+ "\", " + QString::number(l_tmpStr.length()) + "));\n").toAscii());
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

				l_cppFile.write((line+"f_WriteOutput(QString::fromWCharArray(L\""+toCPPEncodeStr(l_tmpStr)+ "\", " + QString::number(l_tmpStr.length()) + "));\n").toAscii());
			}
		}

		QString l_CFromCFTag = GenerateCCodeFromCFTag(l_Tags[c]);
		if (!l_CFromCFTag.isEmpty())
		{
			l_cppFile.write((line + l_CFromCFTag + "\n").toAscii());
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

		l_cppFile.write((line+"f_WriteOutput(QString::fromWCharArray(L\""+toCPPEncodeStr(l_tmpStr)+ "\", " + QString::number(l_tmpStr.length()) + "));\n").toAscii());
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

			l_cppFile.write((line+"f_WriteOutput(QString::fromWCharArray(L\""+toCPPEncodeStr(l_tmpStr)+ "\", " + QString::number(l_tmpStr.length()) + "));\n").toAscii());
		}
	}

	l_cppFile.write("	};\n");
	l_cppFile.write("};\n");
	l_cppFile.write("\n");
	l_cppFile.write("extern \"C\" MY_EXPORT QCFTemplate* createCFMTemplate()\n");
	l_cppFile.write("{\n");
	l_cppFile.write("	return new QCFGeneratedTemplate();\n");
	l_cppFile.write("};\n");
	l_cppFile.close();

	QProcess process;

	// Compile
#ifdef Q_WS_WIN
	QString l_QtPath = getQtDir(); // "C:\\Qt\\2009.04\\qt\\";
	QString l_MingwPath = getMingwDir(); // "C:\\Qt\\2009.04\\mingw\\";
#ifdef QT_NO_DEBUG
	process.start(l_MingwPath+"bin\\g++.exe -c -O2 -frtti -fexceptions -mthreads -Wall -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_NO_DEBUG -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I\""+l_MingwPath+"include\" -I\""+l_QtPath+"include\\QtCore\" -I\""+l_QtPath+"include\\QtNetwork\" -I\""+l_QtPath+"include\" -I\""+p_MKFusionPath+"include\" -o\""+p_MKFusionPath+"templates\\"+l_NewTarget+".o\" \""+p_MKFusionPath+"templates\\"+l_NewTarget+".cpp\"");
#else
	process.start(l_MingwPath+"bin\\g++.exe -c -g  -frtti -fexceptions -mthreads -Wall -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_CORE_LIB -DQT_THREAD_SUPPORT -I\""+l_MingwPath+"include\" -I\""+l_QtPath+"include\\QtCore\" -I\""+l_QtPath+"include\\QtNetwork\" -I\""+l_QtPath+"include\" -I\""+p_MKFusionPath+"include\" -o\""+p_MKFusionPath+"templates\\"+l_NewTarget+".o\" \""+p_MKFusionPath+"templates\\"+l_NewTarget+".cpp\"");
#endif // #ifdef QT_NO_DEBUG
#elif defined Q_WS_X11
#ifdef QT_NO_DEBUG
	process.start("/usr/bin/g++ -c -pipe -O2 -Wall -W -D_REENTRANT -fPIC -DQT_NO_DEBUG -DQT_CORE_LIB -DQT_SHARED -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4 -I\""+p_MKFusionPath+"include\" -o \""+p_MKFusionPath+"templates/"+l_NewTarget+".o\" \""+p_MKFusionPath+"templates/"+l_NewTarget+".cpp\"");
#else
	process.start("/usr/bin/g++ -c -pipe -g -Wall -W -D_REENTRANT -fPIC -DQT_CORE_LIB -DQT_SHARED -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4 -I\""+p_MKFusionPath+"include\" -o \""+p_MKFusionPath+"templates/"+l_NewTarget+".o\" \""+p_MKFusionPath+"templates/"+l_NewTarget+".cpp\"");
#endif // #ifdef QT_NO_DEBUG
#else
#error Windows and Linux OSs are currently supported.
#endif // #ifdef Q_WS_WIN

	bool finished = process.waitForFinished(-1); // TODO: This line blocks on ubuntu.

	//QFile::remove(p_MKFusionPath+"templates/"+l_NewTarget+".cpp");

	if ((finished == false)||(process.exitCode() != 0))
	{
		return "compile error: " + process.readAllStandardError() + process.readAllStandardOutput();
	}

	// Link
#ifdef Q_WS_WIN
#ifdef QT_NO_DEBUG
	process.start(l_MingwPath+"bin\\g++.exe -enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc -Wl,-s -mthreads -Wl -shared -o\""+p_MKFusionPath+"templates\\"+l_NewTarget+".dll\" \""+p_MKFusionPath+"templates\\"+l_NewTarget+".o\" -L\""+l_QtPath+"lib\" \""+p_MKFusionPath+"lib\\mkfusion.a\" -lQtCore4");
#else
	process.start(l_MingwPath+"bin\\g++.exe -enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc -mthreads -Wl -shared -o\""+p_MKFusionPath+"templates\\"+l_NewTarget+".dll\" \""+p_MKFusionPath+"templates\\"+l_NewTarget+".o\" -L\""+l_QtPath+"lib\" \""+p_MKFusionPath+"lib\\mkfusion.a\" -lQtCored4");
#endif
#elif defined Q_WS_X11
#ifdef QT_NO_DEBUG
	process.start("/usr/bin/g++ -Wl,-O1 -shared -o \""+p_MKFusionPath+"templates/"+l_NewTarget+".so\" \""+p_MKFusionPath+"templates/"+l_NewTarget+".o\" -L/usr/lib -lQtCore -lpthread");
#else
	process.start("/usr/bin/g++ -shared -o \""+p_MKFusionPath+"templates/"+l_NewTarget+".so\" \""+p_MKFusionPath+"templates/"+l_NewTarget+".o\" -L/usr/lib -lQtCore -lpthread");
#endif
#else
#error Windows and Linux OSs are currently supported.
#endif
	finished = process.waitForFinished(-1); // TODO: This line blocks on ubuntu.

	QFile::remove(p_MKFusionPath+"templates/"+l_NewTarget+".o");

	if ((finished == false)||(process.exitCode() != 0))
	{
		return "link error: " + process.readAllStandardError() + process.readAllStandardOutput();
	}

	return "";
}

QString QCFGenerator::GenerateVariable(const QString& p_Variable, const QString& p_CanCreateChildren)
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
		&& (l_Variable.startsWith("VARIABLE.", Qt::CaseInsensitive) == 0) \
		&& (l_Variable.compare("VARIABLE", Qt::CaseInsensitive) != 0) \
	   )
	{
		l_Variable = "VARIABLE." + l_Variable;
	}

	QStringList l_StrList = l_Variable.split(".");

	if (l_StrList.size() < 1)
	{
		return "";
	}

	ret = "m_TemplateInstance->m_" + l_StrList[0].toUpper() + ".wr(" + p_CanCreateChildren + ")";

	for(int c = 1; c < l_StrList.size(); c++)
	{
		ret += "[\""+l_StrList[c].toUpper()+"\"]";
	}

	return ret;
}

QString QCFGenerator::GenerateCFExpressionToCExpression(const QCFParserElement& p_CFExpression, QString p_CanCreateChildren = "false")
{
	QString ret;
	QString l_ElementName = p_CFExpression.m_Text;

	switch(p_CFExpression.m_Type)
	{
		case Number:
			ret = "QWDDX(\"" + l_ElementName + "\")";
			break;
		case String:
			if (p_CFExpression.m_ChildElements.size() > 0)
			{
				for(int c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
				{
					if (c == 0)
					{
						ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], p_CanCreateChildren);
					}
					else
					{
						ret += " + " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], p_CanCreateChildren);
					}
				}
			}
			else
			{
				ret = "\""+l_ElementName+"\"";
			}
			break;
		case Variable:
			return GenerateVariable(l_ElementName, p_CanCreateChildren);
			break;
		case Function:;
				ret = "cf_" + m_CFFunctionsDef[l_ElementName.toLower()].m_Name + "(";

				for (int c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
				{
					if (c > 0)
					{
						ret += ", ";
					}
					ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], "false");
				}

				ret += ")";
			break;
		case Operator:
			if (l_ElementName.compare(l_ElementName, "eq", Qt::CaseInsensitive) == 0)
			{
				ret = " == ";
			}
			else if (l_ElementName.compare(l_ElementName, "neq", Qt::CaseInsensitive) == 0)
			{
				ret = " != ";
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
			else
			{
				ret = " " + l_ElementName + " ";
			}
			break;
		case Parameter:
			for (int c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
			{
				ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], "false");
			}
			break;
		case Parameters:
			for (int c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
			{
				if (c == 0)
				{
					ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], "false");
				}
				else
				{
					ret += ", " + GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], "false");
				}
			}

			break;
		case Expression:
			for (int c = 0; c < p_CFExpression.m_ChildElements.size(); c++)
			{
				if (c == 0)
				{
					ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], p_CanCreateChildren);
				}
				else
				{
					ret += GenerateCFExpressionToCExpression(p_CFExpression.m_ChildElements[c], "false");
				}
			}

			break;
		default:;
			break;
	}

	return ret;
}

/*QCFParserElement QCFGenerator::OprimizeQCFParserElement(const QCFParserElement& p_CFExpression)
{
	QCFParserElement ret = p_CFExpression;

	if (ret.m_ChildElements.size() == 0)
	{
		return ret;
	}

	if ((ret.m_Type == Parameter)&&(ret.m_ChildElements.size() == 1))
	{
		if (ret.m_ChildElements[0].m_ChildElements.size() == 1)
		{
			//QList<QCFParserElement> tt = OprimizeQCFParserElement(ret.m_ChildElements[0].m_ChildElements[0]);
			//ret.m_ChildElements = tt;

			ret.m_ChildElements[0] = OprimizeQCFParserElement(ret.m_ChildElements[0].m_ChildElements[0]);

			return ret;
			//return OprimizeQCFParserElement(ret);
		}

		//ret.m_ChildElements[0] = OprimizeQCFParserElement(ret.m_ChildElements[0]);
		//return ret;
	}

	for(int c = 0; c < ret.m_ChildElements.size(); c++)
	{
		if (ret.m_ChildElements[c] == Parameter)
		{
			ret.m_ChildElements[c] = OprimizeQCFParserElement(ret.m_ChildElements[c].m_ChildElements);
		}
		else
		{
			ret.m_ChildElements[c] = OprimizeQCFParserElement(ret.m_ChildElements[c]);
		}
	}

	return ret;
}
*/

bool CFTagHasArgument(const QCFParserTag& p_CFTag, const QString& p_Argument)
{
	foreach(QCFParserElement l_Argument, p_CFTag.m_Arguments.m_ChildElements)
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

QCFParserElement CFTagGetArgumentObject(const QCFParserTag& p_CFTag, const QString& p_Argument)
{
	foreach(QCFParserElement l_Argument, p_CFTag.m_Arguments.m_ChildElements)
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

QString QCFGenerator::CFTagGetArgument(const QCFParserTag& p_CFTag, const QString& p_Argument, const QString& p_CreateVars = "false")
{
	foreach(QCFParserElement l_Argument, p_CFTag.m_Arguments.m_ChildElements)
	{
		if ((l_Argument.m_Type != CFTagArgument)||(l_Argument.m_ChildElements.size() < 1))
		{
			continue;
		}

		if (l_Argument.m_ChildElements[0].m_Text.compare(p_Argument, Qt::CaseInsensitive) == 0)
		{
			QCFParserElement l_temp = l_Argument;
			if (l_temp.m_ChildElements.size() > 1){l_temp.m_ChildElements.removeFirst();}
			if (l_temp.m_ChildElements.size() > 1){l_temp.m_ChildElements.removeFirst();}

			//return GenerateCFExpressionToCExpression(OprimizeQCFParserElement(l_temp), p_CreateVars);
			return GenerateCFExpressionToCExpression(l_temp, p_CreateVars);
		}
	}

	return "";
}

QString QCFGenerator::GenerateCCodeFromCFTag(const QCFParserTag& p_CFTag)
{
	if (p_CFTag.m_TagType == ExpressionTagType)
	{
		//return "f_WriteOutput(" + GenerateCFExpressionToCExpression(OprimizeQCFParserElement(p_CFTag.m_Arguments), "false") + ");";
		return "f_WriteOutput(" + GenerateCFExpressionToCExpression(p_CFTag.m_Arguments, "false") + ");";
	}

	if(!p_CFTag.m_Name.compare("cfabort", Qt::CaseInsensitive))
	{
		if (CFTagHasArgument(p_CFTag, "showError"))
		{
			return "throw QMKFusionExpressionException(" + CFTagGetArgument(p_CFTag, "showError") + ");";
		}
		else
		{
			return "throw QMKFusionCFAbortException();";
		}
	}
	else if(!p_CFTag.m_Name.compare("cfbreak", Qt::CaseInsensitive))
	{
		return "break;";
	}
	else if(!p_CFTag.m_Name.compare("cfdump", Qt::CaseInsensitive))
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

		//return "f_WriteOutput(mk_cfdump("+GenerateCFExpressionToCExpression(OprimizeQCFParserElement(p_CFTag.m_Arguments.m_ChildElements[0].m_ChildElements[2]), "false")+"));";
		return "f_WriteOutput(mk_cfdump("+GenerateCFExpressionToCExpression(p_CFTag.m_Arguments.m_ChildElements[0].m_ChildElements[2], "false")+"));";
	}
	else if(!p_CFTag.m_Name.compare("cfloop", Qt::CaseInsensitive))
	{
		if (p_CFTag.m_TagType == CFTagType)
		{
			if ((CFTagHasArgument(p_CFTag, "index"))&&(CFTagHasArgument(p_CFTag, "from"))&&(CFTagHasArgument(p_CFTag, "to")))
			{
				QString l_Step;
				QString l_Comparation;

				if (CFTagHasArgument(p_CFTag, "step"))
				{
					l_Step = CFTagGetArgument(p_CFTag, "step");
				}
				else
				{
					l_Step = "1";
				}

				if (l_Step[0] == '-')
				{
					l_Comparation = " >= ";
				}
				else
				{
					l_Comparation = " <= ";
				}

				QCFParserElement l_Index = CFTagGetArgumentObject(p_CFTag, "index");
				QString l_IndexStr = l_Index.m_ChildElements[2].m_Text;

				if ((l_Index.m_Type != Error)&&(l_Index.m_ChildElements.size() == 3))
				{
					return "for (" + GenerateVariable(l_IndexStr, "true") + " = " + CFTagGetArgument(p_CFTag, "from") + "; " + GenerateVariable(l_IndexStr, "false") + l_Comparation + CFTagGetArgument(p_CFTag, "to") + "; " + GenerateVariable(l_IndexStr, "false") + " = " + GenerateVariable(l_IndexStr, "false") + " + " + l_Step + ") {";
				}
			}
		}

		if (p_CFTag.m_TagType == EndCFTagType)
		{
			return "}";
		}
	}
	else if(!p_CFTag.m_Name.compare("cfset", Qt::CaseInsensitive))
	{
		//QCFParserElement l_OptimizedElements = OprimizeQCFParserElement(p_CFTag.m_Arguments);
		QCFParserElement l_OptimizedElements = p_CFTag.m_Arguments;
		QString ret;

//		log("m_ChildElements.size() = " + QString::number(l_OptimizedElements.m_ChildElements.size()));

		if ((l_OptimizedElements.m_ChildElements.size() > 1)&&(l_OptimizedElements.m_ChildElements[0].m_Type == Variable)&&(l_OptimizedElements.m_ChildElements[1].m_Type == Operator)&&(l_OptimizedElements.m_ChildElements[1].m_Text == "="))
		{
			ret = GenerateCFExpressionToCExpression(l_OptimizedElements, "true");
		}
		else
		{
			ret = GenerateCFExpressionToCExpression(l_OptimizedElements, "false");
		}

		if (ret != "")
		{
			return ret+";";
		}
	}
	else if(!p_CFTag.m_Name.compare("cfoutput", Qt::CaseInsensitive))
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
	else if(!p_CFTag.m_Name.compare("cfif", Qt::CaseInsensitive))
	{
		if (p_CFTag.m_TagType == CFTagType)
		{
			//return "if (" + GenerateCFExpressionToCExpression(OprimizeQCFParserElement(p_CFTag.m_Arguments), "false") + ") {";
			return "if (" + GenerateCFExpressionToCExpression(p_CFTag.m_Arguments, "false") + ") {";
		}
		if (p_CFTag.m_TagType == EndCFTagType)
		{
			return "}";
		}
	}
	else if(!p_CFTag.m_Name.compare("cfelse", Qt::CaseInsensitive))
	{
		if (p_CFTag.m_TagType == CFTagType)
		{
			return "} else {";
		}
	}
	else if(!p_CFTag.m_Name.compare("cfelseif", Qt::CaseInsensitive))
	{
		if (p_CFTag.m_TagType == CFTagType)
		{
			//return "} else if(" + GenerateCFExpressionToCExpression(OprimizeQCFParserElement(p_CFTag.m_Arguments), "false") + ") {";
			return "} else if(" + GenerateCFExpressionToCExpression(p_CFTag.m_Arguments, "false") + ") {";
		}
	}

	return "";
}
