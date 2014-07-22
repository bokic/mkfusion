lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

TEMPLATE = lib
QT       =
CONFIG  += debug_and_release c++11
DESTDIR  = ../../../install/windows

DEPENDPATH  += .
INCLUDEPATH += .

LIBS   += -static-libgcc -static-libstdc++

SOURCES = uninstall.cpp
HEADERS = uninstall.h
