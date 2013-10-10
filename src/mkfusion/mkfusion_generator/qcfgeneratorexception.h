#ifndef QCFGENERATOREXCEPTION_H
#define QCFGENERATOREXCEPTION_H

#include <qtconcurrentexception.h>
#include <QString>


class QCFGeneratorException : public QException
{
public:
    QCFGeneratorException(const QCFGeneratorException &other)
        : QException()
        , m_Message(other.m_Message)
        , m_pos(other.m_pos)
    {
    }

    QCFGeneratorException(const QString &message, int pos)
        : QException()
        , m_Message(message)
        , m_pos(pos)
    {
	}

    ~QCFGeneratorException() throw() {}

	void raise() const { throw *this; }
    QException *clone() const { return new QCFGeneratorException(*this); }

    QString m_Message;
    int m_pos;
};

#endif // QCFGENERATOREXCEPTION_H

