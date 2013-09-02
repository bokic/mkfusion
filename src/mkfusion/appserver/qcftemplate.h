#ifndef QCFTEMPLATE_H
#define QCFTEMPLATE_H

#include "qcfrunningtemplate.h"

#include <QObject>
#include <QString>

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
	QCFTemplate();
	virtual ~QCFTemplate();
    virtual void run(QCFRunningTemplate *p_TemplateInstance);

    void f_WriteOutput(const QString &p_Text);
    void f_WriteOutput(const QWDDX &p_Wddx);
    void f_Include(const QString &p_template);
    void f_Param(const QString &name);
    void f_Param(const QString &name, const QWDDX &p_default);
    void f_Application(const QString &name, bool sessionManagement, bool setClientCookies);
    void startQuery();
    QWDDX endQuery(const QString &p_DataSource);
    void removeCustomFunctionsFromThisTemplate();
    void addCustomFunction(const QString &functionName, std::function<QWDDX (QCFRunningTemplate *, const QList<QWDDX> &arguments)> function);

	QCFRunningTemplate *m_TemplateInstance;
	QIsTemplateModified m_isModified;
    QHash<QString, std::function<QWDDX (QCFRunningTemplate *, const QList<QWDDX> &arguments)>> m_TemplateCustomFunctions;
};

typedef QCFTemplate* (*createCFMTemplateDef)();

#endif // QCFTEMPLATE_H
