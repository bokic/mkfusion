TEMPLATE = app
TARGET = parsertest1

DESTDIR = ../../../bin
OBJECTS_DIR = ../../../obj/parsertest_debug
MOC_DIR = ../../../obj/parsertest_debug
RCC_DIR =  ../../../obj/parsertest_debug
UI_DIR =  ../../../obj/parsertest_debug
DEPENDPATH = . ../../cfparser/
INCLUDEPATH = . ../../cfparser/

HEADERS = \
	../cfparser/qcfparser.h \
	../cfparser/qcffunction.h \
	../cfparser/qcftag.h \
	../cfparser/qcf8.h \
	parsertest1.h

#Source files
SOURCES = \
	../cfparser/qcfparser.cpp \
	../cfparser/qcffunction.cpp \
	../cfparser/qcftag.cpp \
	../cfparser/qcf8.cpp \
	parsertest1.cpp \
	main.cpp

#Forms
FORMS = parsertest1.ui

#Resource file(s)
# RESOURCES = parsertest1.qrc
