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
    static QString toCPPEncodeStr(const QString &str);
    QString compile(QCFParser &p_Parser, const QString &p_Target, const QString &p_MKFusionPath, const QString &p_CopyGeneratedFilesToPath);
    QString GenerateVariable(const QString &p_Variable, const QString &p_Funct_params = "", const QString &p_Funct_local_vars = "");
    QString GenerateCFExpressionToCExpression(const QCFParserElement &p_CFExpression, const QString &funct_params = "", QString *funct_local_vars = nullptr);
    QCFParserElement OptimizeQCFParserElement(QCFParserElement p_CFExpression);
    QString ParseAndGenerateCppExpressionFromString(const QString str);
    QString CFTagGetArgumentPlain(const QCFParserTag &p_CFTag, const QString &p_Argument);
    QString CFTagGetArgument(const QCFParserTag &p_CFTag, const QString &p_Argument);
    QString CFTagGetArgumentAsString(const QCFParserTag &p_CFTag, const QString &p_Argument);
    QString CFTagGetArgumentAsNumber(const QCFParserTag &p_CFTag, const QString &p_Argument);
    QString CFTagGetArgumentAsBool(const QCFParserTag &p_CFTag, const QString &p_Argument);
    QString GenerateCCodeFromCFTag(const QCFParserTag &p_CFTag);
    static void rebuildPrecompiledHeader(const QString &p_MKFusionPath);
private:
    static QStringList commonCompileSwitches(const QString &p_MKFusionPath);
    QHash<QString, QCFTag> m_CFTagsDef;
    QHash<QString, QCFFunction> m_CFFunctionsDef;
    QHash<QString, QString> m_CustomTagsPrefixes;
    bool m_EnableCFOutputOnly;
    int m_InsideCFOutputTag;
    bool m_InsideCFQueryTag;
    QString m_Tabs;
    QList<const QCFParserTag *> m_SwitchTags;
    QList<const QCFParserTag *> m_NestedTags;
    QList<int> m_SwitchCaseCount;
};

#endif // QCFGENERATOR_H
