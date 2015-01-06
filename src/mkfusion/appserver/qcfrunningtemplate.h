#ifndef QCFRUNNINGTEMPLATE_H
#define QCFRUNNINGTEMPLATE_H

#include "qwddx.h"
#include "common.h"

#include <QLocalSocket>
#include <QMultiHash>
#include <QLibrary>
#include <QHash>

#include <functional>

class QCFServer;

class QCFRunningTemplate : public QObject
{
    Q_OBJECT
public:
    friend class QCFTemplate;

    enum OutputType {OutputTypeContent, OutputTypeQuery};

    QCFRunningTemplate();
    virtual ~QCFRunningTemplate();
    void cf_WriteOutput(const QString &string);
    void setExecutionPositionTo(int row, int column);

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
    QString m_QueryOutput;
    QList<QWDDX> m_QueryParams;
    qint32 m_CFOutput;
    QString m_ContentType;
    int m_StatusCode;
    QMultiHash<QString, QString> m_Header;
    bool m_HeadersSent;
    QLocalSocket *m_Socket;
    QCFServer *m_CFServer;
    QCFRunningTemplate_Request m_Request;
    OutputType m_OutputType;
    QWDDX m_SetCookies;
    QHash<QString, std::function<QWDDX (QCFRunningTemplate *, const QList<QWDDX> &arguments)>> m_CustomFunctions;
    QHash<QString, QLibrary *> m_LoadedTemplates;
    QHash<QString, QCFFileUpload> m_FileUpload;
    bool m_Timeout;

signals:
    void finished();

public slots:
    void worker();
private:
    void *compileAndLoadTemplate(const QString &filename, const QString &uri);
    void runApplicationTemplate();
    void processPostData(QByteArray post);
};

#endif // QCFRUNNINGTEMPLATE_H
