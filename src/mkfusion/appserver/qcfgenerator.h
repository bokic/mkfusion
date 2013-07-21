#ifndef QCFGENERATOR_H
#define QCFGENERATOR_H

#include "qcffunction.h"
#include "qcfparser.h"
#include <qcftag.h>
#include <QString>
#include <QHash>

class QCFGenerator
{
public:
	QCFGenerator();
	QString compile(QCFParser&, const QString&, const QString&);
	QString GenerateVariable(const QString&);
	QString GenerateCFExpressionToCExpression(const QCFParserElement&);
	QCFParserElement OprimizeQCFParserElement(QCFParserElement);
    QString CFTagGetArgumentPlain(const QCFParserTag&, const QString&);
	QString CFTagGetArgument(const QCFParserTag&, const QString&);
	QString GenerateCCodeFromCFTag(const QCFParserTag&);
private:
	QHash<QString, QCFTag> m_CFTagsDef;
	QHash<QString, QCFFunction> m_CFFunctionsDef;
	bool m_EnableCFOutputOnly;
	quint32 m_Tabs;
};

#endif // QCFGENERATOR_H
