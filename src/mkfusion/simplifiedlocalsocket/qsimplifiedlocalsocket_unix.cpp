#include <qsimplifiedlocalsocket.h>
#include <QIODevice>
#include <QDir>

#include <netinet/in.h>
#include <sys/un.h>
#include <poll.h>

QSimplifiedLocalSocket::QSimplifiedLocalSocket()
{
	m_Handle = 0;
}

QSimplifiedLocalSocket::~QSimplifiedLocalSocket()
{
	if (m_Handle)
	{
		::close(m_Handle);
	}
}

void QSimplifiedLocalSocket::connectToServer(QString p_Name, int msecs)
{
	if (m_Handle)
	{
		::close(m_Handle);
	}

	m_Handle = ::socket(PF_LOCAL, SOCK_DGRAM, 0);
	m_Timeout = msecs;

	QString l_Name = p_Name;
	struct sockaddr_un l_SocketName;

	if (!l_Name.startsWith('/'))
	{
		l_Name = '/' + l_Name;
	}
	else
	{
		l_Name = QDir::tempPath() + '/' + p_Name;
	}

	l_SocketName.sun_family = AF_LOCAL;
	QByteArray l_AsciiName = p_Name.toAscii();

	::strncpy(l_SocketName.sun_path, l_AsciiName.constData(), l_AsciiName.count() + 1);


	::bind(m_Handle, (struct sockaddr *) &l_SocketName, SUN_LEN(&l_SocketName));

}

bool QSimplifiedLocalSocket::waitForConnected()
{
	return isValid();
}

int QSimplifiedLocalSocket::write(QByteArray p_Data)
{
	if (!isValid())
	{
		return -1;
	}

	return ::write(m_Handle, p_Data.constData(), p_Data.count());
}

bool QSimplifiedLocalSocket::isValid()
{
	if (m_Handle == 0)
	{
		return false;
	}

	return (::write(m_Handle, NULL, 0) == 0);
}

bool QSimplifiedLocalSocket::waitForReadyRead()
{
	pollfd l_poll;

	if (!isValid())
	{
		return false;
	}

	return ::poll(&l_poll, POLLIN, m_Timeout) > 0;
}

QByteArray QSimplifiedLocalSocket::readAll()
{
	QByteArray ret;

	if (isValid())
	{
		int l_size = ::recv(m_Handle, NULL, 0, MSG_PEEK);

		ret.resize(l_size);

		int l_recieved = ::recv(m_Handle, ret.data(), l_size, 0);

		if (l_recieved < 0)
		{
			return QByteArray();
		}

		if (l_size != l_recieved)
		{
			ret.resize(l_recieved);
		}
	}

	return ret;
}

