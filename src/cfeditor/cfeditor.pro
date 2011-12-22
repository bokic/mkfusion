QT       = core gui network xml webkit
CONFIG  += debug_and_release
#MAKEFILE = ../../obj/cfeditor/Makefile
DESTDIR  = ../../bin

debug {
	OBJECTS_DIR = ../../obj/cfeditor/debug
	MOC_DIR     = ../../obj/cfeditor/debug
	RCC_DIR     = ../../obj/cfeditor/debug
	UI_DIR      = ../../obj/cfeditor/debug
}
release {
	OBJECTS_DIR = ../../obj/cfeditor/release
	MOC_DIR     = ../../obj/cfeditor/release
	RCC_DIR     = ../../obj/cfeditor/release
	UI_DIR      = ../../obj/cfeditor/release
}

win32 {
    DEPENDPATH  += . codeeditwidget/ rds/ ../textparser/ ../../libs/libssh/include/
    INCLUDEPATH += . codeeditwidget/ rds/ ../textparser/ ../../libs/libssh/include/
} else {
    DEPENDPATH  += . codeeditwidget/ rds/ ../textparser/
    INCLUDEPATH += . codeeditwidget/ rds/ ../textparser/
}

win32: {
	LIBS += ../../libs/libssh/lib/libssh.dll.a
} else {
	LIBS += -lssh
}

# Main app
SOURCES = main.cpp qappmainwindow.cpp qprojectproperties.cpp
HEADERS =          qappmainwindow.h   qprojectproperties.h
FORMS   =          qappmainwindow.ui  qprojectproperties.ui

# RDS
SOURCES += rds/qabstractrdsservice.cpp rds/qrdsserver.cpp rds/qfileioservice.cpp rds/qdatabaseservice.cpp
HEADERS += rds/qabstractrdsservice.h   rds/qrdsserver.h   rds/qfileioservice.h   rds/qdatabaseservice.h

# Project Loader abstraction and implementation.
SOURCES += qproject.cpp qlocalproject.cpp qrdsproject.cpp qftpproject.cpp qsftpproject.cpp
HEADERS += qproject.h   qlocalproject.h   qrdsproject.h   qftpproject.h   qsftpproject.h

# QProjectFile class(used for sorted display of dirs and files)
SOURCES += qprojectfile.cpp
HEADERS += qprojectfile.h

# QAdvancedTreeWidget(extends QTreeWidget by adding keyPress signal)
SOURCES += qadvancedtreewidget.cpp
HEADERS += qadvancedtreewidget.h

# Custom(QtCreator looklike) edit widget
SOURCES += codeeditwidget/qcodeeditwidget.cpp
HEADERS += codeeditwidget/qcodeeditwidget.h

# TextParser
SOURCES += ../textparser/qtextparser.cpp
HEADERS += ../textparser/qtextparser.h


# Resources
RESOURCES += cfeditor.qrc
win32:RC_FILE = cfeditor.rc
