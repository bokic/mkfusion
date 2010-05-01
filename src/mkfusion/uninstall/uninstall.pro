TEMPLATE = lib
QT       =
CONFIG  += debug_and_release
#MAKEFILE = ../../../obj/mkfusion/uninstall/Makefile
DESTDIR  = ../../../WINDOWS

debug {
	OBJECTS_DIR = ../../../obj/mkfusion/uninstall/debug
	MOC_DIR     = ../../../obj/mkfusion/uninstall/debug
	RCC_DIR     = ../../../obj/mkfusion/uninstall/debug
	UI_DIR      = ../../../obj/mkfusion/uninstall/debug
}
release {
}

DEPENDPATH  += .
INCLUDEPATH += .

SOURCES = uninstall.cpp
HEADERS = uninstall.h
