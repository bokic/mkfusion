TEMPLATE = app
TARGET = parsertest2
QT -= gui
QT += network
CONFIG  += qtestlib

DESTDIR = ../../../bin
OBJECTS_DIR = ../../../obj/parsertest2_debug
MOC_DIR = ../../../obj/parsertest2_debug
RCC_DIR =  ../../../obj/parsertest2_debug
UI_DIR =  ../../../obj/parsertest2_debug
DEPENDPATH += . ../../cfparser ../../mkfusion/appserver
INCLUDEPATH += . ../../cfparser ../../mkfusion/appserver

# Input
SOURCES += main.cpp \
	../../cfparser/qcfparser.cpp \
	../../cfparser/qcf8.cpp \
	../../cfparser/qcftag.cpp \
	../../cfparser/qcffunction.cpp

HEADERS += \
	../../cfparser/qcfparser.h \
	../../cfparser/qcf8.h \
	../../cfparser/qcftag.h \
	../../cfparser/qcffunction.h
