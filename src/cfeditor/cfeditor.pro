TEMPLATE = app
QT += network \
    webkit \
    xml

DESTDIR = ../../bin
OBJECTS_DIR = ../../obj/cfeditor_debug
MOC_DIR = ../../obj/cfeditor_debug
RCC_DIR =  ../../obj/cfeditor_debug
UI_DIR =  ../../obj/cfeditor_debug
DEPENDPATH += . codeeditwidget/ rds/ ../cfparser/ ../../libs/libssh/include/
INCLUDEPATH += . codeeditwidget/ rds/ ../cfparser/ ../../libs/libssh/include/

win32:LIBS += ../../libs/libssh/lib/libssh.dll.a
unix:LIBS += /usr/lib/libssh.so

# Input
HEADERS = qappmainwindow.h \
    qprojectproperties.h \
    ../cfparser/qcfparser.h \
    ../cfparser/qcf8.h \
    ../cfparser/qcffunction.h \
    ../cfparser/qcftag.h
SOURCES = main.cpp \
    qappmainwindow.cpp \
    qprojectproperties.cpp \
    ../cfparser/qcfparser.cpp \
    ../cfparser/qcf8.cpp \
    ../cfparser/qcffunction.cpp \
    ../cfparser/qcftag.cpp
FORMS += qprojectproperties.ui
HEADERS += rds/qabstractrdsservice.h \
    rds/qrdsserver.h \
    rds/qfileioservice.h \
    rds/qdatabaseservice.h
SOURCES += rds/qabstractrdsservice.cpp \
    rds/qrdsserver.cpp \
    rds/qfileioservice.cpp \
    rds/qdatabaseservice.cpp
HEADERS += qproject.h \
    qlocalproject.h \
    qrdsproject.h \
    qftpproject.h \
    qsftpproject.h
SOURCES += qproject.cpp \
    qlocalproject.cpp \
    qrdsproject.cpp \
    qftpproject.cpp \
    qsftpproject.cpp
HEADERS += qprojectfile.h
SOURCES += qprojectfile.cpp
HEADERS += qadvancedtreewidget.h
SOURCES += qadvancedtreewidget.cpp
HEADERS += codeeditwidget/qcodeeditwidget.h
SOURCES += codeeditwidget/qcodeeditwidget.cpp

HEADERS += ../../libs/libssh/include/libssh/libssh.h \
    ../../libs/libssh/include/libssh/sftp.h

# Resource file(s)
RESOURCES += cfeditor.qrc
win32:RC_FILE = cfeditor.rc
