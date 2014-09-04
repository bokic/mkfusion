/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Solutions component.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qtservice.h"
#include "qtservice_p.h"
#include <QCoreApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include <QStringList>
#include <QFile>
#include <QTimer>
#include <QDir>
#include <pwd.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include <sys/stat.h>
#include <QMap>
#include <QSettings>
#include <QProcess>

static QString encodeName(const QString &name, bool allowUpper = false)
{
    QString n = name.toLower();
    QString legal = QLatin1String("abcdefghijklmnopqrstuvwxyz1234567890");
    if (allowUpper)
        legal += QLatin1String("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    int pos = 0;
    while (pos < n.size()) {
	if (legal.indexOf(n[pos]) == -1)
	    n.remove(pos, 1);
	else
	    ++pos;
    }
    return n;
}

static bool sendCmd(const QString &serviceName, const QString &cmd)
{
    bool retValue = false;
    QLocalSocket sock;
    sock.connectToServer(serviceName);
    sock.open();
    if (sock.isOpen()) {
        sock.write(QString(cmd+"\r\n").toLatin1().constData());
        sock.waitForBytesWritten();
        sock.waitForReadyRead();
        QString reply = sock.readAll();
        if (reply == QLatin1String("true"))
            retValue = true;
	sock.close();
    }
    return retValue;
}

static QString absPath(const QString &path)
{
    QString ret;
    if (path[0] != QChar('/')) { // Not an absolute path
        int slashpos;
        if ((slashpos = path.lastIndexOf('/')) != -1) { // Relative path
            QDir dir = QDir::current();
            dir.cd(path.left(slashpos));
            ret = dir.absolutePath();
        } else { // Need to search $PATH
            char *envPath = ::getenv("PATH");
            if (envPath) {
                QStringList envPaths = QString::fromLocal8Bit(envPath).split(':');
                for (int i = 0; i < envPaths.size(); ++i) {
                    if (QFile::exists(envPaths.at(i) + QLatin1String("/") + QString(path))) {
                        QDir dir(envPaths.at(i));
                        ret = dir.absolutePath();
                        break;
                    }
                }
            }
        }
    } else {
        QFileInfo fi(path);
        ret = fi.absolutePath();
    }
    return ret;
}

QString QtServiceBasePrivate::filePath() const
{
    QString ret;
    if (args.isEmpty())
        return ret;
    QFileInfo fi(args[0]);
    QDir dir(absPath(args[0]));
    return dir.absoluteFilePath(fi.fileName());
}


QString QtServiceController::serviceDescription() const
{
    QSettings settings(QSettings::SystemScope, "QtSoftware");
    settings.beginGroup("services");
    settings.beginGroup(serviceName());

    QString desc = settings.value("description").toString();

    settings.endGroup();
    settings.endGroup();

    return desc;
}

QtServiceController::StartupType QtServiceController::startupType() const
{
    QSettings settings(QSettings::SystemScope, "QtSoftware");
    settings.beginGroup("services");
    settings.beginGroup(serviceName());

    StartupType startupType = (StartupType)settings.value("startupType").toInt();

    settings.endGroup();
    settings.endGroup();

    return startupType;
}

QString QtServiceController::serviceFilePath() const
{
    QSettings settings(QSettings::SystemScope, "QtSoftware");
    settings.beginGroup("services");
    settings.beginGroup(serviceName());

    QString path = settings.value("path").toString();

    settings.endGroup();
    settings.endGroup();

    return path;
}

bool QtServiceController::uninstall()
{
    QSettings settings(QSettings::SystemScope, "QtSoftware");
    settings.beginGroup("services");

    settings.remove(serviceName());

    settings.endGroup();
    settings.sync();

    QSettings::Status ret = settings.status();
    if (ret == QSettings::AccessError) {
        fprintf(stderr, "Cannot uninstall \"%s\". Cannot write to: %s. Check permissions.\n",
                serviceName().toLatin1().constData(),
                settings.fileName().toLatin1().constData());
    }
    return (ret == QSettings::NoError);
}


bool QtServiceController::start(const QStringList &arguments)
{
    if (!isInstalled())
        return false;
    if (isRunning())
        return false;
    return QProcess::startDetached(serviceFilePath(), arguments);
}

bool QtServiceController::stop()
{
    return sendCmd(serviceName(), QLatin1String("terminate"));
}

bool QtServiceController::pause()
{
    return sendCmd(serviceName(), QLatin1String("pause"));
}

bool QtServiceController::resume()
{
    return sendCmd(serviceName(), QLatin1String("resume"));
}

bool QtServiceController::sendCommand(int code)
{
    return sendCmd(serviceName(), QString(QLatin1String("num:") + QString::number(code)));
}

bool QtServiceController::isInstalled() const
{
    QSettings settings(QSettings::SystemScope, "QtSoftware");
    settings.beginGroup("services");

    QStringList list = settings.childGroups();

    settings.endGroup();

    QStringListIterator it(list);
    while (it.hasNext()) {
        if (it.next() == serviceName())
            return true;
    }

    return false;
}

bool QtServiceController::isRunning() const
{
    QLocalSocket sock;
    sock.connectToServer(serviceName());
    sock.open();
    return sock.isOpen();
}




///////////////////////////////////

class QtServiceSysPrivate : public QLocalServer
{
    Q_OBJECT
public:
    QtServiceSysPrivate();
    ~QtServiceSysPrivate();

    char *ident;

    QtServiceBase::ServiceFlags serviceFlags;

protected:
    void incomingConnection(quintptr socketDescriptor);

private slots:
    void slotReady();
    void slotClosed();

private:
    QString getCommand(const QLocalSocket *socket);
    QMap<const QLocalSocket *, QString> cache;
};

QtServiceSysPrivate::QtServiceSysPrivate()
    : QLocalServer(), ident(0), serviceFlags(0)
{
}

QtServiceSysPrivate::~QtServiceSysPrivate()
{
    if (ident)
	delete[] ident;
}

void QtServiceSysPrivate::incomingConnection(quintptr socketDescriptor)
{
    QLocalSocket *s = new QLocalSocket(this);
    s->setSocketDescriptor(socketDescriptor);
    connect(s, &QLocalSocket::readyRead, this, &QtServiceSysPrivate::slotReady);
    connect(s, &QLocalSocket::disconnected, this, &QtServiceSysPrivate::slotClosed);
}

void QtServiceSysPrivate::slotReady()
{
    QLocalSocket *s = (QLocalSocket *)sender();
    cache[s] += QString(s->readAll());
    QString cmd = getCommand(s);
    while (!cmd.isEmpty()) {
        bool retValue = false;
	if (cmd == QLatin1String("terminate")) {
            if (!(serviceFlags & QtServiceBase::CannotBeStopped)) {
                QtServiceBase::instance()->stop();
                QCoreApplication::instance()->quit();
                retValue = true;
            }
        } else if (cmd == QLatin1String("pause")) {
            if (serviceFlags & QtServiceBase::CanBeSuspended) {
                QtServiceBase::instance()->pause();
                retValue = true;
            }
        } else if (cmd == QLatin1String("resume")) {
            if (serviceFlags & QtServiceBase::CanBeSuspended) {
                QtServiceBase::instance()->resume();
                retValue = true;
            }
        } else if (cmd == QLatin1String("alive")) {
            retValue = true;
        } else if (cmd.length() > 4 && cmd.left(4) == QLatin1String("num:")) {
	    cmd = cmd.mid(4);
            QtServiceBase::instance()->processCommand(cmd.toInt());
            retValue = true;
	}
        QString retString;
        if (retValue)
            retString = QLatin1String("true");
        else
            retString = QLatin1String("false");
        s->write(retString.toLatin1().constData());
        s->flush();
	cmd = getCommand(s);
    }
}

void QtServiceSysPrivate::slotClosed()
{
    QLocalSocket *s = (QLocalSocket *)sender();
    s->deleteLater();
}

QString QtServiceSysPrivate::getCommand(const QLocalSocket *socket)
{
    int pos = cache[socket].indexOf("\r\n");
    if (pos >= 0) {
	QString ret = cache[socket].left(pos);
	cache[socket].remove(0, pos+2);
	return ret;
    }
    return "";
}

#include "qtservice_unix.moc"

bool QtServiceBasePrivate::sysInit()
{
    sysd = new QtServiceSysPrivate;
    sysd->serviceFlags = serviceFlags;

    return sysd->listen(controller.serviceName());
}

void QtServiceBasePrivate::sysCleanup()
{
    if (sysd) {
        sysd->close();
        delete sysd;
        sysd = 0;
    }
}

bool QtServiceBasePrivate::start()
{
    if (sendCmd(controller.serviceName(), "alive")) {
        // Already running
        return false;
    }
    // Could just call controller.start() here, but that would fail if
    // we're not installed. We do not want to strictly require installation.
    ::setenv("QTSERVICE_RUN", "1", 1);  // Tell the detached process it's it
    return QProcess::startDetached(filePath(), args.mid(1), "/");
}

bool QtServiceBasePrivate::install(const QString &account, const QString &password)
{
    Q_UNUSED(account)
    Q_UNUSED(password)
    QSettings settings(QSettings::SystemScope, "QtSoftware");

    settings.beginGroup("services");
    settings.beginGroup(controller.serviceName());

    settings.setValue("path", filePath());
    settings.setValue("description", serviceDescription);
    settings.setValue("automaticStartup", startupType);

    settings.endGroup();
    settings.endGroup();
    settings.sync();

    QSettings::Status ret = settings.status();
    if (ret == QSettings::AccessError) {
        fprintf(stderr, "Cannot install \"%s\". Cannot write to: %s. Check permissions.\n",
                controller.serviceName().toLatin1().constData(),
                settings.fileName().toLatin1().constData());
    }
    return (ret == QSettings::NoError);
}

void QtServiceBase::logMessage(const QString &message, QtServiceBase::MessageType type,
			    int, uint, const QByteArray &)
{
    if (!d_ptr->sysd)
        return;
    int st;
    switch(type) {
        case QtServiceBase::Error:
	    st = LOG_ERR;
	    break;
        case QtServiceBase::Warning:
            st = LOG_WARNING;
	    break;
        default:
	    st = LOG_INFO;
    }
    if (!d_ptr->sysd->ident) {
        QString tmp = encodeName(serviceName(), true);
        int len = tmp.toLocal8Bit().size();
        d_ptr->sysd->ident = new char[len+1];
        d_ptr->sysd->ident[len] = '\0';
        ::memcpy(d_ptr->sysd->ident, tmp.toLocal8Bit().constData(), len);
    }
    openlog(d_ptr->sysd->ident, LOG_PID, LOG_DAEMON);
    for(const QString &line: message.split('\n'))
        syslog(st, "%s", line.toLocal8Bit().constData());
    closelog();
}

void QtServiceBase::setServiceFlags(QtServiceBase::ServiceFlags flags)
{
    if (d_ptr->serviceFlags == flags)
        return;
    d_ptr->serviceFlags = flags;
    if (d_ptr->sysd)
        d_ptr->sysd->serviceFlags = flags;
}

