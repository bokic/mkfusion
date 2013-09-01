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
    QString compile(QCFParser &p_Parser, const QString &p_Target, const QString &p_MKFusionPath);
    QString GenerateVariable(const QString &p_Variable, const QString &p_Funct_params = "", const QString &p_Funct_local_vars = "");
    QString GenerateCFExpressionToCExpression(const QCFParserElement &p_CFExpression, const QString &funct_params = "", QString funct_local_vars = "");
    QCFParserElement OprimizeQCFParserElement(QCFParserElement p_CFExpression);
    QString CFTagGetArgumentPlain(const QCFParserTag &p_CFTag, const QString &p_Argument);
    QString CFTagGetArgument(const QCFParserTag &p_CFTag, const QString &p_Argument);
    QString GenerateCCodeFromCFTag(const QCFParserTag &p_CFTag);
private:
	QHash<QString, QCFTag> m_CFTagsDef;
	QHash<QString, QCFFunction> m_CFFunctionsDef;
	bool m_EnableCFOutputOnly;
	quint32 m_Tabs;
};

#endif // QCFGENERATOR_H
