#ifndef COMMON_H
#define COMMON_H

#include "qmkfusionexception.h"
#include "qwddx.h"

#include <QString>


struct QCFRunningTemplate_Request
{
	QString m_AuthType;
	QString m_User;
	QString m_Filename;
	QString m_Accept;
	QString m_AcceptEncoding;
	QString m_AcceptLanguage;
	QString m_Connection;
	QString m_RemoteHost;
	QString m_Referer;
	QString m_UserAgent;
    QString m_Cookie;
	QString m_Args;
	QString m_Method;
	QString m_Protocol;
	QString m_Host;
	QString m_URI;
};

#ifdef Q_OS_WIN
#define MY_EXPORT __declspec(dllexport)
#else
#define MY_EXPORT
#endif

void log(const QString &p_filename, const QString& p_Line);
QString WriteException(const QMKFusionException &ex, const QCFRunningTemplate_Request &r);

extern "C" MY_EXPORT QString mk_cfdump(const QWDDX&);
extern "C" MY_EXPORT QWDDX callCustomFunction(const QString &functionName, const QList<QWDDX> &arguments);
extern "C" MY_EXPORT void updateVariableInt(QWDDX &dest, int key, const QWDDX &value);
extern "C" MY_EXPORT void updateVariableStr(QWDDX &dest, const char *key, const QWDDX &value);
extern "C" MY_EXPORT void updateVariableQStr(QWDDX &dest, const QString &key, const QWDDX &value);
extern "C" MY_EXPORT void updateVariable(QWDDX &dest, const QWDDX &key, const QWDDX &value);

#endif // COMMON_H
