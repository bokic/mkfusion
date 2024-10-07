lessThan(QT_MAJOR_VERSION, 6) {
    error("Unsupported Qt version(Needs Qt6).")
}

TEMPLATE  = lib
QT        = core
CONFIG   += debug_and_release c++11
TARGET    = mod_mkfusion
DESTDIR   = ../../../bin

DEPENDPATH  += . ../simplifiedlocalsocket
INCLUDEPATH += . ../simplifiedlocalsocket


CONFIG += link_pkgconfig
PKGCONFIG += apr-1

INCLUDEPATH  += /usr/include/httpd /usr/include/apache2

# Input
SOURCES        = mod_mkfusion.cpp
SOURCES       += ../simplifiedlocalsocket/qsimplifiedlocalsocket_unix.cpp
HEADERS        = ../simplifiedlocalsocket/qsimplifiedlocalsocket.h
