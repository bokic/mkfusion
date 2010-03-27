#ifndef QCFFUNCTION_H
#define QCFFUNCTION_H

#include <QObject>
#include <QString>

class QCFFunctionArgument : public QObject
{
public:
	enum ArgumentType {TypeConstant, TypeExpression, TypeVariable};
	enum ArgumentDataType {ArgumentDataTypeBool, ArgumentDataTypeInt, ArgumentDataTypeDouble, ArgumentDataTypeString, ArgumentDataTypeDateTime, ArgumentDataTypeQWDDX, ArgumentDataTypeAny};

	QCFFunctionArgument();
	QCFFunctionArgument(const QCFFunctionArgument&);
	QCFFunctionArgument(ArgumentDataType, bool = false, ArgumentType = QCFFunctionArgument::TypeExpression);
	QCFFunctionArgument& operator=(const QCFFunctionArgument&);
	ArgumentDataType m_DataType;
	ArgumentType m_Type;
	bool m_Required;
};
class QCFFunction : public QObject
{
public:
	enum ReturnType {ReturnVoid, ReturnBool, ReturnInt, ReturnDouble, ReturnString, ReturnDateTime, ReturnQWDDX};

	QCFFunction();
	QCFFunction(const QCFFunction&);
	QCFFunction(const QString&, ReturnType);
	QCFFunction& operator=(const QCFFunction&);
	void setName(const QString&);
	const QString& getName();
	QString m_Name;
	ReturnType m_ReturnType;
	QList<QCFFunctionArgument> m_Arguments;
};

#endif // QCFFUNCTION_H
