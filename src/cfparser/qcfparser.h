#pragma once

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

enum QCFParserElementType {Boolean, Number, String, Variable, Function, Operator, SharpExpression, CodeBlock, Expression, SubExpression, Parameters, Parameter, CFScript, CFComment, CFTagExpression, CFTagArguments, CFTagArgument, ObjectFunction, VariableMember, Keyword, Error, Null};
enum QCFParserErrorType {NoError, ForcedTerminationError, ParsingError, InvalidCloseTagError, InvalidCFTagError, InvalidArgumentError, InvalidArgumentTypeError, InvalidNestedTagPositionError};
enum QCFParserTagType {UnknownTagType, CFTagType, EndCFTagType, CommentTagType, ExpressionTagType};
enum QCFParserMode {FullParseMode, CompilerMode};
enum QCFParserFileType {QCFParserTemplateFile, QCFParserComponentFile};


struct QCFParserElement
{
    QCFParserElementType m_Type;
    QString m_Text;
    int m_Position;
    int m_Size;
    QList<QCFParserElement> m_ChildElements;
    QCFParserElement()
        : m_Type(Null)
        , m_Position(0)
        , m_Size(0)
    {
    }

    bool operator==(const struct QCFParserElement &other) const
    {
        if (
            (m_Type == other.m_Type)&&
            (m_Text == other.m_Text)&&
            (m_Position == other.m_Position)&&
            (m_Size == other.m_Size)&&
            (m_ChildElements == other.m_ChildElements)
        )
        {
            return true;
        }

        return false;
    }
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
    QCFParserTag()
        : m_Start(0)
        , m_Length(0)
        , m_TagType(UnknownTagType)
        , m_InlineClosedTag(false)
        , m_OtherTag(nullptr)
    {
    }

    bool operator==(const struct QCFParserTag &other) const
    {
        if (
            (m_Start == other.m_Start)&&
            (m_Length == other.m_Length)&&
            (m_Name == other.m_Name)&&
            (m_TagType == other.m_TagType)&&
            (m_Arguments == other.m_Arguments)&&
            (m_InlineClosedTag == other.m_InlineClosedTag)&&
            (m_OtherTag == other.m_OtherTag)
        )
        {
            return true;
        }

        return false;
    }

    bool operator!=(const struct QCFParserTag &other) const
    {
        QString thisName;
        QString otherName;

        if (m_TagType != CommentTagType)
        {
            thisName = m_Name;
            otherName = other.m_Name;
        }

        if (
            (m_Start == other.m_Start)&&
            (m_Length == other.m_Length)&&
            (thisName == otherName)&&
            (m_TagType == other.m_TagType)&&
            (m_Arguments == other.m_Arguments)&&
            (m_InlineClosedTag == other.m_InlineClosedTag)//&&
            //(m_OtherTag == other.m_OtherTag)
        )
        {
            return false;
        }

        return true;
    }
};

class QCFParser : public QObject
{
public:
    friend class QCFGenerator;

    QCFParser();
    explicit QCFParser(QCFParserMode mode, QCFParserFileType filetype);
    QString error();
    QString getText() const;
    quint32 getErrorPosition();
    QCFParserErrorType parse(const QFileInfo &p_File, bool *p_Terminate = nullptr);
    QCFParserErrorType parse(const QString &p_Text, bool *p_Terminate = nullptr);
    QCFParserErrorType buildTagTree();
    QCFParserErrorType validate();
    QCFParserErrorType prioritizeOperators();
    QList<QCFParserTag> getTags() const;
    QList<QCFParserElement> getScriptFunctions(QList<QCFParserTag> const p_Tags) const;
    QList<QCFParserTag> getTagFunctions(QList<QCFParserTag> const p_Tags) const;
    QList<QCFParserTag> getFunctionArguments(const QCFParserTag &p_Function) const;
    QString m_FileName;
    qint64 m_FileSize;
    uint m_FileModifyDateTime;
    bool m_InsideCFScript;
    QStringList m_TagPrefixes;
    QCFParserFileType m_FileType;

private:
    QList<QCFParserTag> m_Tags;
    QHash<QString, QCFTag> m_CFTagsDef;
    QHash<QString, QCFFunction> m_CFFunctionsDef;
    quint32 m_ErrorPosition;
    QString m_Error;
    QString m_Text;
    QCFParserMode m_Mode;
    static bool TrimCFCode(const QString &p_Text, int &p_Offset);
    bool isValidVarChar(const QString &p_Text, int index);
    QCFParserElement ParseCFCode(const QString &p_Text, const qint32 p_Offset, const QCFParserElementType p_ElementType, QCFParserElement *parent);
    quint32 FindCFCommentSize(const QString &p_Text, quint32 p_Position);
    QCFParserErrorType prioritizeOperatorsRecursive(QCFParserElement &element, const QList<QStringList> &priorities);
    static quint32 GetLineNumberFromPosition(const QString &p_FileContent, int p_FileOffset);
    static quint32 GetColumnNumberFromPosition(const QString &p_FileContent, int p_FileOffset);
};
