#include <qsimplifiedlocalsocket.h>
#include <QIODevice>
#include <QDir>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

QSimplifiedLocalSocket::QSimplifiedLocalSocket()
{
	m_Handle = 0;
}

QSimplifiedLocalSocket::~QSimplifiedLocalSocket()
{
	close();
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
    QByteArray l_AsciiName = l_Name.toLatin1();

	::strncpy(l_SocketName.sun_path, l_AsciiName.constData(), l_AsciiName.count() + 1);

	int c = ::connect(m_Handle, (struct sockaddr *) &l_SocketName, SUN_LEN(&l_SocketName));
	int t = errno;

    Q_UNUSED(c); // TODO: make use of this variable.
    Q_UNUSED(t); // TODO: make use of this variable.
}

bool QSimplifiedLocalSocket::waitForConnected()
{
	return isValid();
}

int QSimplifiedLocalSocket::write(QByteArray p_Data)
{
	if (m_Handle == 0)
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

	pollfd poolh;
	poolh.fd = m_Handle;

	// Don't say unvalid until all bytes are readed.
	//poolh.events = POLLIN;
	//int ret = poll(&poolh, 1, 0);

	//if (ret > 0)
	//{
	//	return true;
	//}

	poolh.events = POLLHUP;

	int ret = poll(&poolh, 1, 0);

	return (ret == 0);
}

bool QSimplifiedLocalSocket::waitForReadyRead()
{
	if (m_Handle == 0)
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

	if (m_Handle != 0)
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

void QSimplifiedLocalSocket::close()
{
	if (m_Handle)
	{
		::close(m_Handle);
		m_Handle = 0;
	}
}
