QT       = core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += debug_and_release
DESTDIR  = ../../../bin

DEFINES  += DEBUG_QTEXTPARSER

debug {
	OBJECTS_DIR = ../../../obj/tests/parsertest1_new/debug
	MOC_DIR     = ../../../obj/tests/parsertest1_new/debug
	RCC_DIR     = ../../../obj/tests/parsertest1_new/debug
	UI_DIR      = ../../../obj/tests/parsertest1_new/debug
}
release {
	OBJECTS_DIR = ../../../obj/tests/parsertest1_new/release
	MOC_DIR     = ../../../obj/tests/parsertest1_new/release
	RCC_DIR     = ../../../obj/tests/parsertest1_new/release
	UI_DIR      = ../../../obj/tests/parsertest1_new/release
}

DEPENDPATH  = . ../../textparser/
INCLUDEPATH = . ../../textparser/

SOURCES     = main.cpp parsertest1_new.cpp qdetail.cpp ../../textparser/qtextparser.cpp
HEADERS     =          parsertest1_new.h   qdetail.h   ../../textparser/qtextparser.h
FORMS       =          parsertest1_new.ui  qdetail.ui
