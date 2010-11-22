QT       = core gui
CONFIG  += debug_and_release
#MAKEFILE = ../../../obj/tests/parsertest1/Makefile
DESTDIR  = ../../../bin
DEFINES += ENABLE_CFSCRIPT

debug {
	OBJECTS_DIR = ../../../obj/tests/parsertest1/debug
	MOC_DIR     = ../../../obj/tests/parsertest1/debug
	RCC_DIR     = ../../../obj/tests/parsertest1/debug
	UI_DIR      = ../../../obj/tests/parsertest1/debug
}
release {
	OBJECTS_DIR = ../../../obj/tests/parsertest1/release
	MOC_DIR     = ../../../obj/tests/parsertest1/release
	RCC_DIR     = ../../../obj/tests/parsertest1/release
	UI_DIR      = ../../../obj/tests/parsertest1/release
}

DEPENDPATH  = . ../../cfparser/
INCLUDEPATH = . ../../cfparser/

SOURCES     = main.cpp parsertest1.cpp qdetail.cpp ../cfparser/qcfparser.cpp ../cfparser/qcffunction.cpp ../cfparser/qcftag.cpp ../cfparser/qcf8.cpp
HEADERS     =          parsertest1.h   qdetail.h   ../cfparser/qcfparser.h   ../cfparser/qcffunction.h   ../cfparser/qcftag.h   ../cfparser/qcf8.h
FORMS       =          parsertest1.ui  qdetail.ui
