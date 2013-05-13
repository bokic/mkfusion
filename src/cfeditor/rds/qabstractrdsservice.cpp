#include "qabstractrdsservice.h"
#include <QTextCodec>
#include <QTcpSocket>
#include <QVector>
#include <QBuffer>
#include <QThread>
#include <QMap>
#include <QUrl>

QAbstractRDSService::QAbstractRDSService(): QObject()
{
}

QByteArray QAbstractRDSService::StringToSTR(QString p_String)
{
        QByteArray l_ba = p_String.toUtf8(); // TODO: hardcoded utf-8
        return QByteArray("STR:") + QString::number(l_ba.length()).toLatin1() + QByteArray(":") + l_ba;
}

QByteArray QAbstractRDSService::EncodePassword(QByteArray p_Password)
{
	return StringToHex(XORString(p_Password));
}

QVector<QByteArray> QAbstractRDSService::BreakByteArrayIntoVector(QByteArray p_ByteArray)
{
	QVector<QByteArray> ret;
	QByteArray str;

	int pos = readToColon(str, p_ByteArray, 0);
	int count = str.toInt();
	for(int c = 0; c < count; c++)
	{
		pos = readToColon(str, p_ByteArray, pos + 1);

		if (pos <= 0)
			break;

		int count2 = str.toInt();
		ret.append(p_ByteArray.mid(pos + 1, count2));
		pos += count2;
	}

	return ret;
}

QByteArray QAbstractRDSService::generateRDSCommandSocketOutput(QString url, QByteArray post)
{
	QUrl l_url(url);
	QString l_Port;

	int port = l_url.port();
	if (port == -1)
		port = 80;

	if (port == 80)
		l_Port = "";
	else
		l_Port = ":" + QString::number(port);

	QString path = url.right(url.size() - url.indexOf(l_url.host()) - l_url.host().size());
	path = path.right(path.size() - path.indexOf('/'));

	QString toSend = "POST " + path + " HTTP/1.0\r\nHost: " + l_url.host() + l_Port + "\r\nConnection: close\r\nUser-Agent: Mozilla/3.0 (compatible; Macromedia RDS Client)\r\nAccept: text/html, */*\r\nAccept-Encoding: deflate\r\nContent-type: text/html\r\nContent-length: " + QString::number(post.size()) + "\r\n\r\n";
    return toSend.toLatin1() + post;
}

QByteArray QAbstractRDSService::executeRDSCommandURL(QString url, QByteArray post)
{
	QTcpSocket socket;
	QUrl l_url(url);
	QByteArray ret;

	int port = l_url.port();
	if (port == -1)
		port = 80;

	socket.connectToHost(l_url.host(), port);

    if (!socket.waitForConnected(5000))
	{
        //emit error(socket.error(), socket.errorString());
		//QAbstractSocket::SocketError err = socket.error();
        return ret;
    }

	socket.write(generateRDSCommandSocketOutput(url, post));

	socket.waitForBytesWritten(5000);
	do
	{
		socket.waitForReadyRead(5000);

		ret += socket.readAll();
	} while(socket.state() == QAbstractSocket::ConnectedState);

	int retHeader = ret.indexOf("\r\n\r\n");
	if (retHeader > 0)
	{
		ret = ret.right(ret.size() - retHeader - 4);
	}

	return ret;
}

QByteArray QAbstractRDSService::generatePostFromVector(QRDSServer rdsserver, QVector<QString> map)
{
	QByteArray ret = QByteArray::number(map.size() + 2) + ":";
	QByteArray password = rdsserver.getPromptedPassword();
	if(password == "")
	{
		password = rdsserver.getPassword().toUtf8();
	}

	for(int c = 0; c < map.size(); c++)
	{
		// Todo: Missing file types(for file upload) but I don't know where it is used!
		ret += StringToSTR(map.at(c));
	}

	ret += StringToSTR(rdsserver.getUserName());
	ret += StringToSTR(EncodePassword(password));

	return ret;
}

QByteArray QAbstractRDSService::executeRDSCommandForByteArray(QString command, QRDSServer rdsserver, QVector<QString> map, quint16 port)
{
	QString s2 = prepareURL(rdsserver, command, port);

	QString tt = generatePostFromVector(rdsserver, map);

	return executeRDSCommandURL(s2, generatePostFromVector(rdsserver, map));
}

// Protected:

QString QAbstractRDSService::prepareURL(QRDSServer rdsserver, QString command, quint16 port)
{
	QString ret = "http://" + rdsserver.getHostName();

	if (port != 80)
        {
		ret += ":" + QString::number(port);
        }

	QString content = rdsserver.getContextRoot().trimmed();
	if((content!="")&&(content!="/")&&(content!="\\"))
	{
		if(!content.startsWith("/") && !content.startsWith("\\"))
			ret += "/";
		ret += content;
	}
	
	ret += "/CFIDE/main/ide.cfm?CFSRV=IDE&ACTION=" + command;

	return ret;
}

QByteArray QAbstractRDSService::ArgumentsToString(QVector<QString> args)
{
	QByteArray ret;

	foreach(QString item, args)
	{
		ret += StringToSTR(item);
	}
	return ret;
}

QByteArray QAbstractRDSService::executeRDSCommandForByteArray(QString command, QRDSServer rdsserver, QVector<QString> map)
{
	return executeRDSCommandForByteArray(command, rdsserver, map, rdsserver.getPort());
}

// Private:

QByteArray QAbstractRDSService::StringToHex(QByteArray s)
{
	const char hextable[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	QByteArray ret;
	for (int c = 0; c < s.length(); c++)
	{
		char ch = s.at(c);
		ret += hextable[ch >> 4];
		ret += hextable[ch & 0x0F];
	}
	return ret;
}

QByteArray QAbstractRDSService::GetKeyForLength(int p_Length)
{
	QByteArray ret;
	int l_Segments = p_Length / 8; // lenght of "4p0L@r1$"

	for(int c = 0; c <= l_Segments; c++)
		ret = ret + "4p0L@r1$";

	return ret.left(p_Length);
}

QByteArray QAbstractRDSService::XORString(QByteArray p_String)
{
	QByteArray ret;
	int l_StringLen = p_String.length();
	QByteArray l_Key = GetKeyForLength(l_StringLen);

	for(int c = 0; c < l_StringLen; c++)
		ret += (p_String.at(c) ^ l_Key.at(c));

	return ret;
}

int QAbstractRDSService::readToColon(QByteArray& str, QByteArray buf, int offset)
{
	str = "";

	int c = offset;
	int ret = -1;

	for(;;)
	{
		if (c >= buf.size())
			break;

		if (buf.at(c) == ':')
		{
			ret = c;
			break;
		}

		str += buf.at(c);

		c++;
	}
	return ret;
}
