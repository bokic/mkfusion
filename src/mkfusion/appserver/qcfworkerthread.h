#ifndef QCFWORKERTHREAD_H
#define QCFWORKERTHREAD_H

#include "qmkfusionexception.h"
#include "qcfvariant.h"

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

struct QCFRequest
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
    explicit QCFWorkerThread(QObject *parent = 0);
    virtual ~QCFWorkerThread();

    void setSocket(QLocalSocket *socket);

signals:

public slots:

protected:
    void run() override;
    virtual void executePage();

public:
    void processPostData(QByteArray post);
    bool readRequest();
    bool writeResponse();
    void writeException(const QMKFusionException &ex);
    void runApplicationTemplate();
    void updateVariables();
    static void updateVariableInt(QCFVariant &dest, int key, const QCFVariant &value);
    static void updateVariableStr(QCFVariant &dest, const wchar_t *key, const QCFVariant &value);
    static void updateVariableQStr(QCFVariant &dest, const QString &key, const QCFVariant &value);
    static void updateVariable(QCFVariant &dest, const QCFVariant &key, const QCFVariant &value);
    void f_WriteOutput(const QString &value);
    void f_cfdump(const QCFVariant &var);


    // Class members
    QCFVariant m_CGI;
    QCFVariant m_SERVER;
    QCFVariant m_COOKIE;
    QCFVariant *m_APPLICATION;
    QCFVariant *m_SESSION;
    QCFVariant m_URL;
    QCFVariant m_FORM;
    QCFVariant m_VARIABLES;
    QString m_Output;
    QList<QCFVariant> m_QueryParams;
    qint32 m_CFOutput;
    QString m_ContentType;
    int m_StatusCode;
    QMultiHash<QString, QString> m_Header;
    bool m_HeadersSent;
    QLocalSocket *m_Socket;
    QCFRequest m_Request;
    QCFVariant m_SetCookies;
    QHash<QString, std::function<QCFVariant (QCFWorkerThread *, const QList<QCFVariant> &arguments)>> m_CustomFunctions;
    QHash<QString, QCFFileUpload> m_FileUpload;
    bool m_writtenHeaders;

private:
    static QString f_cfdump_var(const QCFVariant &var);

    bool m_CFDump;
};

#endif // QCFWORKERTHREAD_H
