#include <qsimplifiedlocalsocket.h>
#include <QIODevice>
#include <QDir>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/errno.h>
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

	int c = ::connect(m_Handle, (struct sockaddr *) &l_SocketName, SUN_LEN(&l_SocketName));
	int t = errno;
	c = 0;
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

	fd_set check_set;
	struct timeval to;

	FD_ZERO(&check_set);
	FD_SET(m_Handle, &check_set);

	to.tv_sec = 0;
	to.tv_usec = 0;

	::pe
	return (::select(m_Handle + 1, &check_set, 0, 0, &to) == 0);
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
	QByteArray temp;

	if (isValid())
	{
		forever
		{
			temp.resize(1024);

			int l_size = ::recv(m_Handle, temp.data(), 1024, 0);

			if (l_size == 0)
			{
				break;
			}

			temp.resize(l_size);

			ret.append(temp);
		}
	}

	return ret;
}
