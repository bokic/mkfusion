#ifndef QCFTEMPLATE_H
#define QCFTEMPLATE_H

#include "qcfrunningtemplate.h"

#include <QObject>
#include <QString>

struct QIsTemplateModified {
	QString m_Filename;
	qint64 m_Size;
	uint m_Modified;
};

class Q_DECL_EXPORT QCFTemplate : public QObject
{
public:
	QCFTemplate();
	virtual void run(QCFRunningTemplate*);

	void f_WriteOutput(const QString&);
	void f_WriteOutput(const QWDDX&);

	QCFRunningTemplate* m_TemplateInstance;
	QIsTemplateModified m_isModified;
};

typedef QCFTemplate* (*createCFMTemplateDef)();

#endif // QCFTEMPLATE_H
