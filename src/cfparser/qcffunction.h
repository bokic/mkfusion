#ifndef QCFFUNCTION_H
#define QCFFUNCTION_H

#include <QString>
#include <QObject>
#include <QList>

class QCFFunctionArgument : public QObject
{
public:
	enum QCFFunctionArgumentType {TypeConstant, TypeExpression, TypeVariable, TypeAny};
    enum QCFFunctionArgumentDataType {ArgumentDataTypeBool, ArgumentDataTypeInt, ArgumentDataTypeDouble, ArgumentDataTypeString, ArgumentDataTypeBinary, ArgumentDataTypeDateTime, ArgumentDataTypeQCFVariant, ArgumentDataTypeAny};

	QCFFunctionArgument();
    QCFFunctionArgument(const QCFFunctionArgument &other);
	QCFFunctionArgument(QCFFunctionArgumentDataType p_DataType, bool p_Required = false, QCFFunctionArgumentType p_Type = QCFFunctionArgument::TypeExpression);
    QCFFunctionArgument &operator=(const QCFFunctionArgument &other);
#ifdef Q_COMPILER_RVALUE_REFS
    QCFFunctionArgument &operator=(QCFFunctionArgument &&other);
#endif

	// Class members
	QCFFunctionArgumentDataType m_DataType;
	QCFFunctionArgumentType m_Type;
	bool m_Required;
};

class QCFFunction : public QObject
{
public:
    enum QCFFunctionReturnType {ReturnVoid, ReturnBool, ReturnInt, ReturnDouble, ReturnBinary, ReturnString, ReturnDateTime, ReturnQCFVariant};

	QCFFunction();
    QCFFunction(const QCFFunction &other);
    QCFFunction(const QString &p_FunctionName, QCFFunctionReturnType p_ReturnType, bool p_NeedsThis = false);
    QCFFunction &operator=(const QCFFunction &other);
#ifdef Q_COMPILER_RVALUE_REFS
    QCFFunction &operator=(QCFFunction &&other);
#endif
    void setName(const QString &p_FunctionName);
    const QString &getName();

	// Class members
	QString m_Name;
    bool m_NeedsThis;
	QCFFunctionReturnType m_ReturnType;
	QList<QCFFunctionArgument> m_Arguments;
};

#endif // QCFFUNCTION_H
