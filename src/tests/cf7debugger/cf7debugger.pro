lessThan(QT_MAJOR_VERSION, 6) {
    error("Unsupported Qt version(Needs Qt6).")
}

QT       = core gui widgets network

CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

DEPENDPATH  += .
INCLUDEPATH += .

SOURCES = main.cpp qjdwpsocket.cpp qjdwpdebugger.cpp qappmainwindow.cpp qjdwpcommand.cpp qjdwpgetpathseparatorcommand.cpp qjdwpclassesbysignaturecommand.cpp qjdwpidsizescommand.cpp
HEADERS =          qjdwpsocket.h   qjdwpdebugger.h   qappmainwindow.h   qjdwpcommand.h   qjdwpgetpathseparatorcommand.h   qjdwpclassesbysignaturecommand.h   qjdwpidsizescommand.h
