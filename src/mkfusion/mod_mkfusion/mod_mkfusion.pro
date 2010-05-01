TEMPLATE  = lib
QT        = core
CONFIG   += debug_and_release
TARGET    = mod_mkfusion
#MAKEFILE  = ../../../obj/mkfusion/mod_mkfusion/Makefile
DESTDIR   = ../../../bin

debug {
	OBJECTS_DIR = ../../../obj/mkfusion/mod_mkfusion/debug
	MOC_DIR     = ../../../obj/mkfusion/mod_mkfusion/debug
	RCC_DIR     = ../../../obj/mkfusion/mod_mkfusion/debug
	UI_DIR      = ../../../obj/mkfusion/mod_mkfusion/debug
}
release {
	OBJECTS_DIR = ../../../obj/mkfusion/mod_mkfusion/release
	MOC_DIR     = ../../../obj/mkfusion/mod_mkfusion/release
	RCC_DIR     = ../../../obj/mkfusion/mod_mkfusion/release
	UI_DIR      = ../../../obj/mkfusion/mod_mkfusion/release
}

DEPENDPATH  += . ../simplifiedlocalsocket ../../../libs/apache2/include
INCLUDEPATH += . ../simplifiedlocalsocket ../../../libs/apache2/include

win32:INCLUDEPATH += apache2/include      apr/include apr-util/include
unix:INCLUDEPATH  += /usr/include/apache2 /usr/include/apr-1.0

win32:LIBS += "-L../../../libs/apache2/lib" -llibhttpd -llibapr-1 libpsapi
unix:LIBS += -L/usr/lib/

# Input
SOURCES        = mod_mkfusion.cpp
win32:SOURCES += ../simplifiedlocalsocket/qsimplifiedlocalsocket_win.cpp
unix:SOURCES  += ../simplifiedlocalsocket/qsimplifiedlocalsocket_unix.cpp
HEADERS        = ../simplifiedlocalsocket/qsimplifiedlocalsocket.h
