lessThan(QT_MAJOR_VERSION, 6) {
    error("Unsupported Qt version(Needs Qt6).")
}

QT       = core gui network xml widgets webview webenginewidgets core5compat

CONFIG  += debug_and_release c++11
DESTDIR  = ../../bin

DEPENDPATH  += . codeeditwidget ../textparser
INCLUDEPATH += . codeeditwidget ../textparser
win32:DEPENDPATH  += ../../libs/libssh/include
win32:INCLUDEPATH += ../../libs/libssh/include

win32: {
	LIBS += ../../libs/libssh/lib/libssh.dll.a
} else {
	LIBS += -lssh
}

# Main app
SOURCES = main.cpp qappmainwindow.cpp qprojectproperties.cpp
HEADERS =          qappmainwindow.h   qprojectproperties.h
FORMS   =          qappmainwindow.ui  qprojectproperties.ui

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
HEADERS += ../textparser/qtextparser.h   ../textparser/qtextparserelement.h   ../textparser/qtextparserline.h   ../textparser/qtextparserlanguagedefinitiontoken.h   ../textparser/qtextparserlanguagedefinition.h

# Resources
RESOURCES += cfeditor.qrc
win32:RC_FILE = cfeditor.rc
