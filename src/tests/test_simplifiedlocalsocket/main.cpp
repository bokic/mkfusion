#include <qsimplifiedlocalsocket.h>
#include <QDir>

int main()
{
    QSimplifiedLocalSocket l_localSocket;

    l_localSocket.connectToServer("mkfusion", 1000);

    if (l_localSocket.waitForConnected())
    {
        QByteArray l_Send;
        QDataStream l_IOStream(&l_Send, QIODevice::WriteOnly);
        l_IOStream.setVersion(QDataStream::Qt_4_4);

		l_IOStream << (quint32)0; // Size
		l_IOStream << ""; // Auth_type
		l_IOStream << ""; // User
		l_IOStream << QDir::toNativeSeparators("/var/www/test.cfm").toLatin1(); // File
		l_IOStream << ""; // Accept
		l_IOStream << ""; // Accept-Encoding
		l_IOStream << ""; // Accept-Language
		l_IOStream << ""; // Connection
		l_IOStream << ""; // Host
		l_IOStream << ""; // Referer
		l_IOStream << ""; // User-Agent
		l_IOStream << ""; // args
		l_IOStream << "GET"; // method
		l_IOStream << ""; // Protocol
		l_IOStream.device()->seek(0);
		l_IOStream << (quint32)l_Send.size();

		int l_size = l_localSocket.write(l_Send);

		if (l_size == l_Send.size() + 4) // INFO: 4 = int size
		{
			return -1;
		}

		bool l_HeadersWritten = false;
		qint32 l_HeaderSize = 0;
		QByteArray l_ReadBuf;

		while(l_localSocket.isValid())
		{
			if (l_localSocket.waitForReadyRead())
			{
				l_ReadBuf = l_localSocket.readAll();

				if (l_HeadersWritten == false)
				{
					if (l_HeaderSize == 0)
					{
						if (l_ReadBuf.size() >= 4)
						{
							QDataStream l_HeadersDataStream(&l_ReadBuf, QIODevice::ReadOnly);
							l_HeadersDataStream.setVersion(QDataStream::Qt_4_4);
							l_HeadersDataStream >> l_HeaderSize;
							if ((l_HeaderSize <= 0)||(l_HeaderSize > 0x01000000))
							{
								return -2;
							}
						}
					}

					if ((l_HeaderSize < 4)||(l_ReadBuf.size() < l_HeaderSize))
					{
						continue;
					}

					QByteArray l_Header = l_ReadBuf.left(l_HeaderSize);
					l_ReadBuf = l_ReadBuf.right(l_ReadBuf.size() - l_HeaderSize);

					QDataStream l_HeadersDataStream(&l_Header, QIODevice::ReadOnly);
					l_HeadersDataStream.setVersion(QDataStream::Qt_4_4);
					l_HeadersDataStream >> l_HeaderSize;

					QString l_tempStr;
					l_HeadersDataStream >> l_tempStr;
					QByteArray l_tempByte = l_tempStr.toUtf8();

					int l_Status;
					l_HeadersDataStream >> l_Status;

					qint32 l_HeaderLen;
					l_HeadersDataStream >> l_HeaderLen;
					while(l_HeadersDataStream.atEnd() == false)
					{
						QString key, val;

						l_HeadersDataStream >> key;
						l_HeadersDataStream >> val;
					}
					l_HeadersWritten = true;
				}

				if (l_ReadBuf.size() > 0)
				{
                    qDebug(l_ReadBuf.constData());
				}

				l_ReadBuf.clear();
			}
		}
	}

	return 0;
}
