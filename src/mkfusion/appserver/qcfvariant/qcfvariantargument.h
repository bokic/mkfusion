#ifndef QCFVariantARGUMENT_H
#define QCFVariantARGUMENT_H

#include <QString>


class QCFVariantArgument
{
public:
    QCFVariantArgument();

    QString m_Name;
    QString m_Required;
    QString m_Type;
    QString m_Default;
};

#endif // QCFVariantARGUMENT_H
