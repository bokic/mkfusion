lessThan(QT_MAJOR_VERSION, 6) {
    error("Unsupported Qt version(Needs Qt6).")
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
