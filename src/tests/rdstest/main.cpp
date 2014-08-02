#include "qfileioservice.h"
#include "qdatabaseservice.h"
#include "qdebuggerservice.h"
#include "qcfdebugger.h"
#include "qrdsserver.h"
#include "qwddxutils.h"
#include "qwddx.h"

#include <QCoreApplication>
#include <QStringList>
#include <QVector>
#include <QString>
#include <QList>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    /*QFile file("test.xml");
    file.open(QIODevice::ReadOnly);
    QWDDXUtils utils;
    QWDDX wddx = utils.deserialize(file.readAll());
    QString ttt = utils.serialize(wddx);
    file.close();*/

    QRDSServer rs;
    //rs.setPort(8500);
    //rs.setHostName("192.168.1.117");
    //rs.setPassword("password");

    QMap<QString, QString> map;
    QByteArray ba;

    //QFileIOService fileIO;

    //map.clear();
    //map.insert("NAME", "/var/www/tt/");
    //map.insert("NAME", "c:\\");
    //map.insert("MASK", "");
    //ba = fileIO.ExecuteRDSCommand(rs, QFileIOService::BrowseDirCommand, map);

    //map.clear();
    //map.insert("NAME", "/var/www/tt/Application.cfc");
    //ba = fileIO.ExecuteRDSCommand(rs, QFileIOService::FileReadCommand, map);

    //map.clear();
    //map.insert("NAME", "/var/www/tt/Application2.cfc");
    //map.insert("FILE_CONTENTS", "New Content");
    //ba = fileIO.ExecuteRDSCommand(rs, QFileIOService::FileWriteCommand, map);

    //map.clear();
    //map.insert("NAME", "/var/www/tt/Application2.cfc");
    //map.insert("NEW_NAME", "/var/www/tt/Application3.cfc");
    //ba = fileIO.ExecuteRDSCommand(rs, QFileIOService::FileRenameCommand, map);

    //map.clear();
    //map.insert("NAME", "/var/www/tt/Application3.cfc");
    //ba = fileIO.ExecuteRDSCommand(rs, QFileIOService::FileRemoveFileCommand, map);

    //map.clear();
    //map.insert("NAME", "/var/www/tt/tt/");
    //ba = fileIO.ExecuteRDSCommand(rs, QFileIOService::FileRemoveDirectoryCommand, map);

    //map.clear();
    //map.insert("NAME", "/var/www/tt/index.cfm");
    //ba = fileIO.ExecuteRDSCommand(rs, QFileIOService::FileExistCommand, map);

    //map.clear();
    //map.insert("NAME", "/var/www/tt/t_new");
    //ba = fileIO.ExecuteRDSCommand(rs, QFileIOService::FileCreateDirCommand, map);

    //map.clear();
    //ba = fileIO.ExecuteRDSCommand(rs, QFileIOService::FileGetRootDirCommand, map);

    QDatabaseService dbService;

    //map.clear();
    //ba = dbService.ExecuteRDSCommand(rs, QDatabaseService::GetDataSource, map);
    //QVector<QString> vec = dbService.BreakByteArrayIntoVector(ba);
    //QStringList tttttt = vec.at(0).split(",");

    //map.clear();
    //map.insert("DATASOURCE_NAME", "myhost");
    //ba = dbService.ExecuteRDSCommand(rs, QDatabaseService::GetTablesForDS, map);
    //QVector<QString> vec = dbService.BreakByteArrayIntoVector(ba);
    //QStringList tttttt = vec.at(0).split(",");

    //map.clear();
    //map.insert("DATASOURCE_NAME", "myhost");
    //map.insert("TABLE_NAME", "users");
    //ba = dbService.ExecuteRDSCommand(rs, QDatabaseService::GetColumnsForTable, map);
    //QVector<QString> vec = dbService.BreakByteArrayIntoVector(ba);

    //map.clear();
    //map.insert("DATASOURCE_NAME", "myhost");
    //map.insert("TABLE_NAME", "users");
    //ba = dbService.ExecuteRDSCommand(rs, QDatabaseService::GetPrimaryKeysForTable, map);
    //QVector<QString> vec = dbService.BreakByteArrayIntoVector(ba);

    //map.clear();
    //map.insert("DATASOURCE_NAME", "myhost");
    //map.insert("SQL_STATEMENT", "SELECT * FROM `users`");
    //ba = dbService.ExecuteRDSCommand(rs, QDatabaseService::ExecuteSQLStatement, map);
    //QVector<QString> vec = dbService.BreakByteArrayIntoVector(ba);

    //map.clear();
    //map.insert("DATASOURCE_NAME", "myhost");
    //map.insert("SQL_STATEMENT", "SELECT * FROM `users`");
    //ba = dbService.ExecuteRDSCommand(rs, QDatabaseService::GetSQLMetadata, map);
    //QVector<QString> vec = dbService.BreakByteArrayIntoVector(ba);

    //map.clear();
    //ba = dbService.ExecuteRDSCommand(rs, QDatabaseService::GetSQLSupportedCommands, map);
    //QVector<QString> vec = dbService.BreakByteArrayIntoVector(ba);

    QCFDebugger dbg(rs);
    dbg.setParent(&app);

    dbg.StartDebugger();

    app.exec();

    dbg.StopDebugger();

    // <wddxPacket version='1.0'><header/><data><array length='1'><struct type='java.util.HashMap'><var name='DEBUG_SERVER_PORT'><number>47660.0</number></var><var name='STATUS'><string>RDS_OK</string></var></struct></array></data></wddxPacket>

    return 0;
}
