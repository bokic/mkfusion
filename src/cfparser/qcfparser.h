#ifndef QCFPARSER_H
#define QCFPARSER_H

#include "qcffunction.h"
#include "qcftag.h"

#include <QObject>
#include <QString>
#include <QList>
#include <QHash>

enum QCFParserElementType {Number, String, Variable, Function, Operator, SharpExpression, Expression, SubExpression, Parameters, Parameter, CFScript, CFComment, CFTagExpression, CFTagArguments, CFTagArgument, ObjectFunction, VariableIndex, Error};
enum QCFParserErrorType {NoError, ForcedTerminationError, ParsingError, InvalidCloseTagError, InvalidArgumentError, InvalidArgumentTypeError, InvalidNestedTagPositionError};
enum QCFParserTagType {UnknownTagType, CFTagType, EndCFTagType, CommentTagType, ExpressionTagType};

struct QCFParserElement
{
	QCFParserElementType m_Type;
	QString m_Text;
	int m_Position;
	int m_Size;
	QList<QCFParserElement> m_ChildElements;
};

struct QCFParserTag
{
	int m_Start;
	int m_Length;
	QString m_Name;
	QCFParserTagType m_TagType;
	QCFParserElement m_Arguments;
	bool m_InlineClosedTag;
	qint32 m_EndTag;
};

quint32 GetLineNumberFromPosition(const QString &, const qint32);
quint32 GetColumnNumberFromPosition(const QString &, const qint32);

qint32 FindEndString(QString, qint32);

class QCFParser : public QObject
{
private:
	QList<QCFParserTag> m_Tags;
	QHash<QString, QCFTag> m_CFTagsDef;
	QHash<QString, QCFFunction> m_CFFunctionsDef;
	quint32 m_ErrorPosition;
	QString m_Error;
	QString m_Text;
	static bool TrimCFCode(const QString&, int&);
	QCFParserElement ParseCFCode(const QString&, const qint32, const QCFParserElementType);
	static quint32 FindCFCommentSize(QString, quint32);
public:
	QCFParser();
	QString getError();
	const QString& getText();
	quint32 getErrorPosition();
	QCFParserErrorType Parse(const QString&, bool* = NULL);
	QCFParserErrorType BuildTagTree();
	QList<QCFParserTag> getTags();
	QString m_FileName;
	qint64 m_CFMFileSize;
	uint m_CFMModifyDateTime;
};

#endif // QCFPARSER_H
