#ifndef QCFWORKERTHREAD_H
#define QCFWORKERTHREAD_H

#include "qmkfusionexception.h"
#include "qwddx.h"

#include <QTemporaryFile>
#include <QLocalSocket>
#include <QThread>


struct QCFFileUpload
{
    QCFFileUpload()
        : m_File(nullptr)
    {
    }

    ~QCFFileUpload()
    {
        if (m_File)
        {
            delete m_File;
            m_File = nullptr;
        }
    }

    void createTmpFile()
    {
        m_File = new QTemporaryFile();
    }

    QTemporaryFile *m_File;
    QString m_ContentType;
    QString m_Filename;
};

struct QCFRunningTemplate_Request
{
    QString m_AuthType;
    QString m_User;
    QString m_Filename;
    QString m_Accept;
    QString m_AcceptEncoding;
    QString m_AcceptLanguage;
    QString m_Connection;
    QString m_ContentType;
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

class QCFWorkerThread : public QThread
{
public:
    explicit QCFWorkerThread(QLocalSocket *socket, QObject *parent = 0);
    virtual ~QCFWorkerThread();

signals:

public slots:

protected:
    void run();

private:
    void processPostData(QByteArray post);
    bool readRequest();
    bool writeResponse();
    void writeException(const QMKFusionException &ex);
    static void updateVariableInt(QWDDX &dest, int key, const QWDDX &value);
    static void updateVariableStr(QWDDX &dest, const wchar_t *key, const QWDDX &value);
    static void updateVariableQStr(QWDDX &dest, const QString &key, const QWDDX &value);
    static void updateVariable(QWDDX &dest, const QWDDX &key, const QWDDX &value);

    // Class members
    QWDDX m_CGI;
    QWDDX m_SERVER;
    QWDDX m_COOKIE;
    QWDDX *m_APPLICATION;
    QWDDX *m_SESSION;
    QWDDX m_URL;
    QWDDX m_FORM;
    QWDDX m_VARIABLES;
    QString m_Output;
    QList<QWDDX> m_QueryParams;
    qint32 m_CFOutput;
    QString m_ContentType;
    int m_StatusCode;
    QMultiHash<QString, QString> m_Header;
    bool m_HeadersSent;
    QLocalSocket *m_Socket;
    QCFRunningTemplate_Request m_Request;
    QWDDX m_SetCookies;
    QHash<QString, std::function<QWDDX (QCFWorkerThread *, const QList<QWDDX> &arguments)>> m_CustomFunctions;
    QHash<QString, QCFFileUpload> m_FileUpload;
};

#endif // QCFWORKERTHREAD_H
