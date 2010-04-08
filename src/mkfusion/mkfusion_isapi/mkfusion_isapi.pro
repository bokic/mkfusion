QT += network
QT -= gui
TARGET = mkfusion_isapi
TEMPLATE = lib
DEFINES += MKFUSION_ISAPI_LIBRARY

DESTDIR = ../../../bin
OBJECTS_DIR = ../../../obj/mkfusion_isapi_debug
MOC_DIR = ../../../obj/mkfusion_isapi_debug
RCC_DIR =  ../../../obj/mkfusion_isapi_debug
UI_DIR =  ../../../obj/mkfusion_isapi_debug
DEPENDPATH += . ../../../libs
INCLUDEPATH += . ../../../libs

DEF_FILE = mkfusion_isapi.def
SOURCES = mkfusion_isapi.cpp
HEADERS = 
