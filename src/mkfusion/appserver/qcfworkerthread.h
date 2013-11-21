#ifndef QCFWORKERTHREAD_H
#define QCFWORKERTHREAD_H

#include "qmkfusionexception.h"
#include "qcfvariant.h"

#include <QTemporaryFile>
#include <QLocalSocket>
#include <QThread>
#include <QList>


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
    enum QCustomTagType {QCustomTagTypeModuleName, QCustomTagTypeModuleTemplate, QCustomTagType_, QCustomTagTypeImport};

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
    void f_WriteOutput(const QCFVariant &value);
    void f_WriteOutput(const QString &value);
    void f_WriteOutput(const wchar_t *value);
    void f_Location(const QString &p_URL, int p_StatusCode);
    void f_Location(const QString &p_URL, bool p_AddToken, int p_StatusCode);
    void f_Include(const QString &p_template);
    void f_Param(const QString &name);
    void f_Param(const QString &name, const QCFVariant &p_default);
    bool f_FetchQueryRow(QCFVariant &destination, QCFVariant &query, int row);
    void f_Application(const QString &name, bool sessionManagement, bool setClientCookies);
    void f_FileUploadMove(const QString &destination, const QString &fileField, const QString &accept, const QString &attributes, const QString &mode, const QString &nameConflict, const QString &result);
    void startQuery();
    QCFVariant endQuery(const QString &p_DataSource);
    void endQueryNoReturn(const QString &p_DataSource);
    void addCustomFunction(const QString &functionName, std::function<QCFVariant (QCFWorkerThread *, const QList<QCFVariant> &)> function);
    void f_SetCookie(const QString &name, const QString &value, const QString &expires);
    void startCustomTag(const QString &path, const QString &name, const QCFVariant &attributes, bool hasEndTag, QCustomTagType type);
    bool endCustomTag(const QString &path, const QString &name, QCustomTagType type);
    void f_cfAssociate(const QString &baseTagName, const QString &keyName);
    QCFVariant f_CreateComponent(const QString &component_name);
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
    QList<QCFVariant> m_CustomTags;
    QList<QString> m_NestedOutput;
    QString m_TemplateFilePath;
    qint64 m_TemplateFileSize;
    uint m_TemplateFileModified;

private:
    static QString f_cfdump_var(const QCFVariant &var);

    bool m_CFDump;
};

#endif // QCFWORKERTHREAD_H
