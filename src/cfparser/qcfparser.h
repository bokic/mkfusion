#ifndef QCFPARSER_H
#define QCFPARSER_H

struct QCFParserElement;
struct QCFParserTag;
class QCFParser;

#include "qcffunction.h"
#include "qcftag.h"

#include <QStringList>
#include <QFileInfo>
#include <QString>
#include <QObject>
#include <QList>
#include <QHash>

enum QCFParserElementType {Boolean, Number, String, Variable, Function, Operator, SharpExpression, CodeBlock, Expression, SubExpression, Parameters, Parameter, CFScript, CFComment, CFTagExpression, CFTagArguments, CFTagArgument, ObjectFunction, VariableMember, Keyword, Error};
enum QCFParserErrorType {NoError, ForcedTerminationError, ParsingError, InvalidCloseTagError, InvalidCFTagError, InvalidArgumentError, InvalidArgumentTypeError, InvalidNestedTagPositionError};
enum QCFParserTagType {UnknownTagType, CFTagType, EndCFTagType, CommentTagType, ExpressionTagType};
enum QCFParserMode {FullParseMode, CompilerMode};


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
    struct QCFParserTag *m_OtherTag;
    bool operator==(const struct QCFParserTag &other)
    {
        if (
                (m_Start == other.m_Start)&&
                (m_Length == other.m_Length)&&
                (m_Name == other.m_Name)&&
                (m_TagType == other.m_TagType)&&
                (&m_Arguments == &other.m_Arguments)&& // TODO: recursive check is needed here[QCFParserTag::operator==()]
                (m_InlineClosedTag == other.m_InlineClosedTag)&&
                (m_OtherTag == other.m_OtherTag)
           )
        {
            return true;
        }

        return false;
    }
};

class QCFParser : public QObject
{
public:
    friend class QCFGenerator;

    QCFParser();
    explicit QCFParser(QCFParserMode mode);
    QString error();
    const QString &getText() const;
    quint32 getErrorPosition();
    QCFParserErrorType parse(const QFileInfo &p_File, bool *p_Terminate = nullptr);
    QCFParserErrorType parse(const QString &p_Text, bool *p_Terminate = nullptr);
    QCFParserErrorType buildTagTree();
    QCFParserErrorType validate();
    QCFParserErrorType prioritizeOperators();
    QList<QCFParserTag> getTags() const;
    QHash<QString, QCFTag> getCFTagsDef() const;
    QList<QCFParserElement> getScriptFunctions(QList<QCFParserTag> const p_Tags) const;
    QList<QCFParserTag> getTagFunctions(QList<QCFParserTag> const p_Tags);
    QString m_FileName;
    qint64 m_FileSize;
    uint m_FileModifyDateTime;
    bool m_InsideCFScript;
    QStringList m_TagPrefixes;

private:
	QList<QCFParserTag> m_Tags;
    const QHash<QString, QCFTag> &m_CFTagsDef;
    const QHash<QString, QCFFunction> &m_CFFunctionsDef;
	quint32 m_ErrorPosition;
	QString m_Error;
	QString m_Text;
	QCFParserMode m_Mode;
    static bool TrimCFCode(const QString &p_Text, int &p_Offset);
    bool isValidVarChar(const QString &p_Text, int index);
    QCFParserElement ParseCFCode(const QString &p_Text, const qint32 p_Offset, const QCFParserElementType p_ElementType, QCFParserElement *parent);
    quint32 FindCFCommentSize(const QString &p_Text, quint32 p_Position);
    QCFParserErrorType prioritizeOperatorsRecursive(QCFParserElement &element, const QList<QStringList> &priorities);
    static quint32 GetLineNumberFromPosition(const QString &p_FileContent, const qint32 p_FileOffset);
    static quint32 GetColumnNumberFromPosition(const QString &p_FileContent, const qint32 p_FileOffset);
};

#endif // QCFPARSER_H
