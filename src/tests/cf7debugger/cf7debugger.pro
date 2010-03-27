QT += network
TARGET = cf7debugger
CONFIG -= app_bundle
TEMPLATE = app
DESTDIR = ../../../bin
OBJECTS_DIR = ../../../obj/cf7debugger_debug
MOC_DIR = ../../../obj/cf7debugger_debug
RCC_DIR =  ../../../obj/cf7debugger_debug
UI_DIR =  ../../../obj/cf7debugger_debug
DEPENDPATH += .
INCLUDEPATH += .

HEADERS += qjdwpsocket.h qjdwpdebugger.h qappmainwindow.h qjdwpcommand.h qjdwpgetpathseparatorcommand.h qjdwpclassesbysignaturecommand.h qjdwpidsizescommand.h
SOURCES += main.cpp qjdwpsocket.cpp qjdwpdebugger.cpp qappmainwindow.cpp qjdwpcommand.cpp qjdwpgetpathseparatorcommand.cpp qjdwpclassesbysignaturecommand.cpp qjdwpidsizescommand.cpp
