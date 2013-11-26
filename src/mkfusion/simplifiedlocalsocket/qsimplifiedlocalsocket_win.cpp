#include <qsimplifiedlocalsocket.h>
#include <QIODevice>

QSimplifiedLocalSocket::QSimplifiedLocalSocket()
    : m_Handle(INVALID_HANDLE_VALUE)
{
}

QSimplifiedLocalSocket::~QSimplifiedLocalSocket()
{
	close();
}

void QSimplifiedLocalSocket::connectToServer(QString p_Name, int msecs)
{
	QString pipePath = QLatin1String("\\\\.\\pipe\\");
	QString l_Name;

	if (p_Name.startsWith(pipePath))
		l_Name = p_Name;
	else
		l_Name = pipePath + p_Name;

	forever {
		m_Handle = CreateFile((const wchar_t *)l_Name.utf16(),   // pipe name
								 GENERIC_READ | GENERIC_WRITE,
								 0,              // no sharing
                                 nullptr,           // default security attributes
								 OPEN_EXISTING,  // opens existing pipe
								 FILE_FLAG_OVERLAPPED,
                                 nullptr);          // no template file

		if (m_Handle != INVALID_HANDLE_VALUE)
		{
			COMMTIMEOUTS l_commtimeouts;
			l_commtimeouts.ReadIntervalTimeout = msecs;
			l_commtimeouts.ReadTotalTimeoutConstant = msecs;
			l_commtimeouts.ReadTotalTimeoutMultiplier = 1;
			l_commtimeouts.WriteTotalTimeoutConstant = msecs;
			l_commtimeouts.WriteTotalTimeoutMultiplier = 1;
			SetCommTimeouts(m_Handle, &l_commtimeouts);
			break;
		}
		DWORD error = GetLastError();
		// It is really an error only if it is not ERROR_PIPE_BUSY
		if (ERROR_PIPE_BUSY != error) {
			break;
		}

		// All pipe instances are busy, so wait until connected or up to 5 seconds.
		if (!WaitNamedPipe((const wchar_t *)p_Name.utf16(), 5000))
			break;
	}
}

bool QSimplifiedLocalSocket::waitForConnected()
{
	return isValid();
}

int QSimplifiedLocalSocket::write(QByteArray p_Data)
{
	DWORD ret;

    if (!WriteFile(m_Handle, p_Data.constData(), p_Data.size(), &ret, nullptr))
		return -1;

	return ret;
}

bool QSimplifiedLocalSocket::isValid()
{
	if (m_Handle == INVALID_HANDLE_VALUE)
		return false;

    if (PeekNamedPipe(m_Handle, nullptr, 0, nullptr, nullptr, nullptr))
		return true;

	return false;
}

bool QSimplifiedLocalSocket::waitForReadyRead()
{
	DWORD l_TotalBytesAvail = 0;

	if (m_Handle != INVALID_HANDLE_VALUE)
	{
        PeekNamedPipe(m_Handle, nullptr, 0, nullptr, &l_TotalBytesAvail, nullptr);
	}

	return l_TotalBytesAvail > 0;
}

QByteArray QSimplifiedLocalSocket::readAll()
{
	QByteArray ret;

	if (m_Handle != INVALID_HANDLE_VALUE)
	{
		DWORD l_TotalBytesAvail;
        PeekNamedPipe(m_Handle, nullptr, 0, nullptr, &l_TotalBytesAvail , nullptr);

		ret.resize(l_TotalBytesAvail);

		DWORD l_Readed;
        ReadFile(m_Handle, ret.data(), ret.size(), &l_Readed, nullptr);
		ret.resize(l_Readed);
	}

	return ret;
}

void QSimplifiedLocalSocket::close()
{
	if (m_Handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
	}
}
