lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core gui widgets network

CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

debug {
	OBJECTS_DIR = ../../../obj/tests/cf7debugger/debug
	MOC_DIR     = ../../../obj/tests/cf7debugger/debug
	RCC_DIR     = ../../../obj/tests/cf7debugger/debug
	UI_DIR      = ../../../obj/tests/cf7debugger/debug
}
release {
	OBJECTS_DIR = ../../../obj/tests/cf7debugger/release
	MOC_DIR     = ../../../obj/tests/cf7debugger/release
	RCC_DIR     = ../../../obj/tests/cf7debugger/release
	UI_DIR      = ../../../obj/tests/cf7debugger/release
}

DEPENDPATH  += .
INCLUDEPATH += .

SOURCES = main.cpp qjdwpsocket.cpp qjdwpdebugger.cpp qappmainwindow.cpp qjdwpcommand.cpp qjdwpgetpathseparatorcommand.cpp qjdwpclassesbysignaturecommand.cpp qjdwpidsizescommand.cpp
HEADERS =          qjdwpsocket.h   qjdwpdebugger.h   qappmainwindow.h   qjdwpcommand.h   qjdwpgetpathseparatorcommand.h   qjdwpclassesbysignaturecommand.h   qjdwpidsizescommand.h
