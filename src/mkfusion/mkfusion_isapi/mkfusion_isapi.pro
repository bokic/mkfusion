TEMPLATE = lib
QT       = core network
CONFIG  += debug_and_release
TARGET   = mkfusion_isapi
DEFINES += MKFUSION_ISAPI_LIBRARY
#MAKEFILE = ../../../obj/mkfusion/mkfusion_isapi/Makefile
DESTDIR = ../../../bin

debug {
	OBJECTS_DIR = ../../../obj/mkfusion/mkfusion_isapi/debug
	MOC_DIR     = ../../../obj/mkfusion/mkfusion_isapi/debug
	RCC_DIR     = ../../../obj/mkfusion/mkfusion_isapi/debug
	UI_DIR      = ../../../obj/mkfusion/mkfusion_isapi/debug
}
release {
	OBJECTS_DIR = ../../../obj/mkfusion/mkfusion_isapi/release
	MOC_DIR     = ../../../obj/mkfusion/mkfusion_isapi/release
	RCC_DIR     = ../../../obj/mkfusion/mkfusion_isapi/release
	UI_DIR      = ../../../obj/mkfusion/mkfusion_isapi/release
}

DEPENDPATH  += . ../../../libs
INCLUDEPATH += . ../../../libs

DEF_FILE = $$PWD/mkfusion_isapi.def

SOURCES = mkfusion_isapi.cpp
