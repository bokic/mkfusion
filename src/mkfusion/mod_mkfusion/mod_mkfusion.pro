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

win32:INCLUDEPATH += ../../../libs/apache2/include
unix {
    LSB_RELEASE = $$system(lsb_release -d)

    message( LSB_RELEASE: ($$LSB_RELEASE))

    contains(LSB_RELEASE, Arch Linux) {
        INCLUDEPATH  += /usr/include/httpd /usr/include/apr-1
    }
    !contains(LSB_RELEASE, Arch Linux) {
        INCLUDEPATH  += /usr/include/apache2 /usr/include/apr-1.0
    }
}

win32:LIBS += "-L../../../libs/apache2/lib" -llibhttpd -llibapr-1 libpsapi
unix:LIBS += -L/usr/lib/

# Input
SOURCES        = mod_mkfusion.cpp
win32:SOURCES += ../simplifiedlocalsocket/qsimplifiedlocalsocket_win.cpp
unix:SOURCES  += ../simplifiedlocalsocket/qsimplifiedlocalsocket_unix.cpp
HEADERS        = ../simplifiedlocalsocket/qsimplifiedlocalsocket.h
