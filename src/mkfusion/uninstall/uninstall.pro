QT -= core \
    gui
TARGET = uninstall
TEMPLATE = lib

DESTDIR = ../../../WINDOWS
OBJECTS_DIR = ../../../obj/uninstall_debug
MOC_DIR = ../../../obj/uninstall_debug
RCC_DIR =  ../../../obj/uninstall_debug
UI_DIR =  ../../../obj/uninstall_debug
DEPENDPATH +=  .
INCLUDEPATH += .

SOURCES += uninstall.cpp
HEADERS += uninstall.h
