#include <qsimplifiedlocalsocket.h>
#include <QIODevice>
#include <QDir>

#include <netinet/in.h>
#include <sys/un.h>
#include <fcntl.h>
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

	m_Handle = ::socket(PF_LOCAL, 0x80000 | SOCK_STREAM, 0);
	if (m_Handle == -1)
	{
		m_Handle = ::socket(PF_LOCAL, SOCK_STREAM, 0);
		if (m_Handle == -1)
		{
			m_Handle = 0;
			return;
		}
	}

	if (::fcntl(m_Handle, F_GETFL, 0) == -1)
	{
		if (::fcntl(m_Handle, F_SETFL, 0x0400) == -1)
		{
			::close(m_Handle);
			m_Handle = 0;
			return;
		}
	}

	m_Timeout = msecs;

	QString l_Name = p_Name;
	struct sockaddr_un l_SocketName;

	if (!l_Name.startsWith('/'))
	{
		l_Name = QDir::tempPath() + '/' + l_Name;
	}

	l_SocketName.sun_family = AF_LOCAL;
	QByteArray l_AsciiName = l_Name.toAscii();

	::strncpy(l_SocketName.sun_path, l_AsciiName.constData(), l_AsciiName.count() + 1);

	::connect(m_Handle, (struct sockaddr *) &l_SocketName, SUN_LEN(&l_SocketName));
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
	if (!isValid())
	{
		return false;
	}

	pollfd l_poll;
	l_poll.fd = m_Handle;
	l_poll.events = POLLIN;

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
