QT       = core network
CONFIG  += debug_and_release qtestlib
#MAKEFILE = ../../../obj/tests/parsertest2/Makefile
DESTDIR  = ../../../bin

debug {
	OBJECTS_DIR = ../../../obj/tests/parsertest2/debug
	MOC_DIR     = ../../../obj/tests/parsertest2/debug
	RCC_DIR     = ../../../obj/tests/parsertest2/debug
	UI_DIR      = ../../../obj/tests/parsertest2/debug
}
release {
	OBJECTS_DIR = ../../../obj/tests/parsertest2/release
	MOC_DIR     = ../../../obj/tests/parsertest2/release
	RCC_DIR     = ../../../obj/tests/parsertest2/release
	UI_DIR      = ../../../obj/tests/parsertest2/release
}

DEPENDPATH  += . ../../cfparser ../../mkfusion/appserver
INCLUDEPATH += . ../../cfparser ../../mkfusion/appserver

SOURCES = main.cpp ../../cfparser/qcfparser.cpp ../../cfparser/qcf8.cpp ../../cfparser/qcftag.cpp ../../cfparser/qcffunction.cpp
HEADERS =          ../../cfparser/qcfparser.h   ../../cfparser/qcf8.h   ../../cfparser/qcftag.h   ../../cfparser/qcffunction.h
