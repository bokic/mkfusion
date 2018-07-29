lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

TEMPLATE  = lib
QT        = core
CONFIG   += debug_and_release c++11
TARGET    = mod_mkfusion
DESTDIR   = ../../../bin

DEPENDPATH  += . ../simplifiedlocalsocket
INCLUDEPATH += . ../simplifiedlocalsocket


unix:CONFIG += link_pkgconfig
unix:PKGCONFIG += apr-1

win32:INCLUDEPATH += ../../../libs/apache2/include
unix:INCLUDEPATH  += /usr/include/httpd /usr/include/apache2
win32:LIBS += "-L../../../libs/apache2/lib" -llibhttpd -llibapr-1 libpsapi

# Input
SOURCES        = mod_mkfusion.cpp
win32:SOURCES += ../simplifiedlocalsocket/qsimplifiedlocalsocket_win.cpp
unix:SOURCES  += ../simplifiedlocalsocket/qsimplifiedlocalsocket_unix.cpp
HEADERS        = ../simplifiedlocalsocket/qsimplifiedlocalsocket.h
