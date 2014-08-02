#include "qabstractrdsservice.h"
#include <QTextCodec>
#include <QTcpSocket>
#include <QVector>
#include <QBuffer>
#include <QThread>
#include <QMap>
#include <QUrl>

QAbstractRDSService::QAbstractRDSService()
    : QObject()
{
}

QAbstractRDSService::~QAbstractRDSService()
{
}

QByteArray QAbstractRDSService::StringToSTR(const QString &value)
{
    QByteArray ret, tmp;

    tmp = value.toUtf8(); // TODO: hardcoded utf-8

    ret.append("STR:");
    ret.append(QByteArray::number(tmp.length()));
    ret.append(':');
    ret.append(tmp);

    return ret;
}

QByteArray QAbstractRDSService::EncodePassword(const QByteArray &value)
{
    return XORString(value).toHex();
}

QVector<QByteArray> QAbstractRDSService::BreakByteArrayIntoVector(const QByteArray &value)
{
    QVector<QByteArray> ret;
    QByteArray str;

    int pos = readToColumn(str, value, 0);
    int count = str.toInt();
    for(int c = 0; c < count; c++)
    {
        pos = readToColumn(str, value, pos + 1);

        if (pos <= 0)
            break;

        int count2 = str.toInt();
        ret.append(value.mid(pos + 1, count2));
        pos += count2;
    }

    return ret;
}

QByteArray QAbstractRDSService::generateRDSCommandSocketOutput(const QString &url, const QByteArray &post)
{
    QUrl l_url(url);
    QString portStr;

    int port = l_url.port();
    if ((port < 0x0000)||(port > 0xffff))
        port = 80;

    if (port == 80)
        portStr = "";
    else
        portStr = ":" + QString::number(port);

    QString path = url.right(url.size() - url.indexOf(l_url.host()) - l_url.host().size());
    path = path.right(path.size() - path.indexOf('/'));

    QString toSend = "POST " + path + " HTTP/1.0\r\nHost: " + l_url.host() + portStr + "\r\nConnection: close\r\nUser-Agent: Mozilla/3.0 (compatible; Macromedia RDS Client)\r\nAccept: text/html, */*\r\nAccept-Encoding: deflate\r\nContent-type: text/html\r\nContent-length: " + QString::number(post.size()) + "\r\n\r\n";

    return toSend.toLatin1() + post; // TODO: toLatin1()
}

QByteArray QAbstractRDSService::executeRDSCommandURL(const QString &url, const QByteArray &post)
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
    }
    while(socket.state() == QAbstractSocket::ConnectedState);

    int retHeader = ret.indexOf("\r\n\r\n");
    if (retHeader > 0)
    {
        ret = ret.right(ret.size() - retHeader - 4);
    }

    return ret;
}

QByteArray QAbstractRDSService::generatePostFromVector(const QRDSServer &rdsserver, const QVector<QString> &map)
{
    QByteArray ret;
    QByteArray password;

    ret = QByteArray::number(map.size() + 2) + ":"; // `+ 2` is plus username and plus password.
    password = rdsserver.promptedPassword();

    if(password.isEmpty())
    {
        password = rdsserver.password().toUtf8();
    }

    for(const QString &item : map)
    {
        // TODO: Missing file types(for file upload) but I don't know where it is used!
        ret.append(StringToSTR(item));
    }

    ret.append(StringToSTR(rdsserver.username()));
    ret.append(StringToSTR(EncodePassword(password)));

    return ret;
}

QByteArray QAbstractRDSService::executeRDSCommandForByteArray(const QString &command, const QRDSServer &rdsserver, const QVector<QString> &map, quint16 port)
{
    QString url;
    QByteArray post;

    url = prepareURL(rdsserver, command, port);
    post = generatePostFromVector(rdsserver, map);

    return executeRDSCommandURL(url, post);
}

QString QAbstractRDSService::prepareURL(const QRDSServer &rdsserver, const QString &command, quint16 port)
{
    QString ret, content;

    ret = "http://" + rdsserver.hostname();

    if (port != 80)
    {
        ret.append(":" + QString::number(port));
    }

    content = rdsserver.contextRoot().trimmed();

    if((!content.isEmpty())&&(content != "/")&&(content != "\\"))
    {
        if(!content.startsWith("/") && !content.startsWith("\\"))
        {
            ret.append('/');
        }
        ret.append(content);
    }

    ret.append("/CFIDE/main/ide.cfm?CFSRV=IDE&ACTION=" + command);

    return ret;
}

// Protected Members:
QByteArray QAbstractRDSService::ArgumentsToString(const QVector<QString> &args)
{
    QByteArray ret;

    for(const QString &item: args)
    {
        ret.append(StringToSTR(item));
    }

    return ret;
}

QByteArray QAbstractRDSService::executeRDSCommandForByteArray(const QString &command, const QRDSServer &rdsserver, const QVector<QString> &map)
{
    return executeRDSCommandForByteArray(command, rdsserver, map, rdsserver.port());
}

// Private:
QByteArray QAbstractRDSService::GetKeyForLength(int len)
{
    static const char *fillup = "4p0L@r1$";

    QByteArray ret;
    int segments;

    segments = len / strlen(fillup);

    for(int c = 0; c <= segments; c++)
    {
        ret.append(fillup);
    }

    return ret.left(len);
}

QByteArray QAbstractRDSService::XORString(const QByteArray &value)
{
    QByteArray ret, tmp;
    int len;

    len = value.length();
    tmp = GetKeyForLength(len);

    for(int c = 0; c < len; c++)
    {
        ret.append(value.at(c) ^ tmp.at(c));
    }

    return ret;
}

int QAbstractRDSService::readToColumn(QByteArray &str, const QByteArray &buf, int offset)
{
    str = "";

    int c = offset;
    int ret = -1;

    forever
    {
        if (c >= buf.size())
            break;

        if (buf.at(c) == ':')
        {
            ret = c;
            break;
        }

        str.append(buf.at(c));

        c++;
    }

    return ret;
}
