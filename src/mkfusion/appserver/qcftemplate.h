#ifndef QCFTEMPLATE_H
#define QCFTEMPLATE_H

#include "qcfrunningtemplate.h"

#include <QObject>
#include <QString>

#include <functional>

struct QIsTemplateModified {
	QString m_Filename;
	qint64 m_Size;
	uint m_Modified;
	QIsTemplateModified() {
		m_Size = 0;
		m_Modified = 0;
	}
};

class Q_DECL_EXPORT QCFTemplate : public QObject
{
public:
    enum QCustomTagType {QCustomTagTypeModuleName, QCustomTagTypeModuleTemplate, QCustomTagType_, QCustomTagTypeImport};

    QCFTemplate();
	virtual ~QCFTemplate();
    virtual void run(QCFRunningTemplate *p_TemplateInstance);

    void f_WriteOutput(const QString &p_Text);
    void f_WriteOutput(const QWDDX &p_Wddx);
    void f_Location(const QString &p_URL, int p_StatusCode = 302);
    void f_Location(const QString &p_URL, bool p_AddToken, int p_StatusCode = 302);
    void f_Include(const QString &p_template);
    void f_Param(const QString &name);
    void f_Param(const QString &name, const QWDDX &p_default);
    bool f_FetchQueryRow(QWDDX &destination, QWDDX &query, int row);
    void f_Application(QString name, bool sessionManagement, bool setClientCookies);
    void f_FileUploadMove(const QString &destination, const QString &fileField, const QString &accept, const QString &attributes, const QString &mode, const QString &nameConflict, const QString &result);
    void startQuery();
    QWDDX endQuery(const QString &p_DataSource);
    void endQueryNoReturn(const QString &p_DataSource);
    void addCustomFunction(const QString &functionName, std::function<QWDDX (QCFRunningTemplate *, const QList<QWDDX> &arguments)> function);
    void f_SetCookie(const QString &name, const QString &value, const QString &expires);
    void startCustomTag(const QString &path, const QString &name, const QWDDX &attributes, bool hasEndTag, QCustomTagType type);
    bool endCustomTag(const QString &path, const QString &name, QCustomTagType type);
    void f_cfAssociate(const QString &baseTagName, const QString &keyName);

	QCFRunningTemplate *m_TemplateInstance;
    QList<QWDDX> m_CustomTags;
	QIsTemplateModified m_isModified;
    QHash<QString, std::function<QWDDX (QCFRunningTemplate *, const QList<QWDDX> &arguments)>> m_TemplateCustomFunctions;
};

typedef QCFTemplate* (*createCFMTemplateDef)();

#endif // QCFTEMPLATE_H
