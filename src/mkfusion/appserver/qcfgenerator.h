#ifndef QCFGENERATOR_H
#define QCFGENERATOR_H

#include "qcfparser.h"

class QCFGenerator
{
public:
	QCFGenerator();
	QString compile(QCFParser&, const QString&, const QString&);
	QString GenerateVariable(const QString&, const QString&);
	QString GenerateCFExpressionToCExpression(const QCFParserElement&, QString);
	QCFParserElement OprimizeQCFParserElement(QCFParserElement);
	QString CFTagGetArgument(const QCFParserTag&, const QString&, const QString&);
	QString GenerateCCodeFromCFTag(const QCFParserTag&);
private:
	QHash<QString, QCFTag> m_CFTagsDef;
	QHash<QString, QCFFunction> m_CFFunctionsDef;
	bool m_EnableCFOutputOnly;
	quint32 m_Tabs;
};

#endif // QCFGENERATOR_H
