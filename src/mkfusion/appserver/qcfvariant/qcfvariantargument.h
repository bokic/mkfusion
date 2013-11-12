#ifndef QCFVARIANTARGUMENT_H
#define QCFVARIANTARGUMENT_H

#include <QString>
#include <QList>


class QCFVariantArgument
{
public:
    QCFVariantArgument();
    QCFVariantArgument(const QString &name, const QString &required, const QString &type, const QString &def, const QString &displayName, const QString &hint);
    QCFVariantArgument(const QCFVariantArgument &other);
#ifdef Q_COMPILER_RVALUE_REFS
    QCFVariantArgument &operator=(QCFVariantArgument &&other);
#endif
    QCFVariantArgument &operator=(const QCFVariantArgument &other);

    QString m_Name;
    QString m_Required;
    QString m_Type;
    QString m_Default;
    QString m_DisplayName;
    QString m_Hint;
};

class QCFVariantArgumentList : public QList<QCFVariantArgument>
{
public:
    inline QCFVariantArgumentList() { }
    inline explicit QCFVariantArgumentList(const QCFVariantArgument &i) { append(i); }
    inline QCFVariantArgumentList(const QCFVariantArgumentList &l) : QList<QCFVariantArgument>(l) { }
    inline QCFVariantArgumentList(const QList<QCFVariantArgument> &l) : QList<QCFVariantArgument>(l) { }
#ifdef Q_COMPILER_INITIALIZER_LISTS
    inline QCFVariantArgumentList(std::initializer_list<QCFVariantArgument> args) : QList<QCFVariantArgument>(args) { }
#endif

    inline QCFVariantArgumentList &operator<<(const QCFVariantArgument &arg)
    { append(arg); return *this; }
};

#endif // QCFVARIANTARGUMENT_H
