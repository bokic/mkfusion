#ifndef QCFGENERATOR_H
#define QCFGENERATOR_H

#include "qcffunction.h"
#include "qcfparser.h"
#include "qcftag.h"
#include "qcf8.h"

#include <QString>
#include <QObject>
#include <QHash>


class QCFGenerator
{
public:
    QCFGenerator();
    virtual ~QCFGenerator();

    bool generate(const QString &srcFilePath, const QString &dstFilePath);
    QString error() const;

protected:
    virtual void generateCpp(const QString &p_Target) = 0;
    static QByteArray toCPPEncodedString(const QString &string);
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
    QByteArray GenerateWriteOutput(const QString &output);
    QString tabs(int trim = 0);
    bool isComponent() const;

    QCFParser m_Parser;
    QHash<QString, QString> m_CustomTagsPrefixes;
	bool m_EnableCFOutputOnly;
    int m_Tabs;
    QList<const QCFParserTag *> m_SwitchTags;
    QList<const QCFParserTag *> m_NestedTags;
    QList<int> m_SwitchCaseCount;
    QString m_Error;
};

#endif // QCFGENERATOR_H
