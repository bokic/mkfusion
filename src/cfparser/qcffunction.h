#ifndef QCFFUNCTION_H
#define QCFFUNCTION_H

#include <QString>
#include <QObject>
#include <QList>

class QCFFunctionArgument : public QObject
{
public:
	enum QCFFunctionArgumentType {TypeConstant, TypeExpression, TypeVariable, TypeAny};
	enum QCFFunctionArgumentDataType {ArgumentDataTypeBool, ArgumentDataTypeInt, ArgumentDataTypeDouble, ArgumentDataTypeString, ArgumentDataTypeDateTime, ArgumentDataTypeQWDDX, ArgumentDataTypeAny};

	QCFFunctionArgument();
	QCFFunctionArgument(const QCFFunctionArgument &other);
	QCFFunctionArgument(QCFFunctionArgumentDataType p_DataType, bool p_Required = false, QCFFunctionArgumentType p_Type = QCFFunctionArgument::TypeExpression);
	QCFFunctionArgument& operator=(const QCFFunctionArgument &other);

	// Class members
	QCFFunctionArgumentDataType m_DataType;
	QCFFunctionArgumentType m_Type;
	bool m_Required;
};

class QCFFunction : public QObject
{
public:
	enum QCFFunctionReturnType {ReturnVoid, ReturnBool, ReturnInt, ReturnDouble, ReturnString, ReturnDateTime, ReturnQWDDX};

	QCFFunction();
	QCFFunction(const QCFFunction &other);
	QCFFunction(const QString &, QCFFunctionReturnType, const QList<QCFFunctionArgument> &p_Arguments = QList<QCFFunctionArgument>());
	QCFFunction& operator=(const QCFFunction &other);
	void setName(const QString &p_FunctionName);
	const QString& getName();

	// Class members
	QString m_Name;
	QCFFunctionReturnType m_ReturnType;
	QList<QCFFunctionArgument> m_Arguments;
};

#endif // QCFFUNCTION_H
