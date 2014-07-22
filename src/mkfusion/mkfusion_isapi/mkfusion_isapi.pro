lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

TEMPLATE = lib
QT       = core network
CONFIG  += debug_and_release
TARGET   = mkfusion_isapi
DEFINES += MKFUSION_ISAPI_LIBRARY
DESTDIR = ../../../bin

DEPENDPATH  += . ../../../libs
INCLUDEPATH += . ../../../libs

DEF_FILE = $$PWD/mkfusion_isapi.def

SOURCES = mkfusion_isapi.cpp
