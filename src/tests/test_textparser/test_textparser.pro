QT       += core xml
QT       -= gui
CONFIG  += debug_and_release
#MAKEFILE = ../../../obj/tests/test_textparser/Makefile
DESTDIR  = ../../../bin

debug {
	OBJECTS_DIR = ../../../obj/tests/test_textparser/debug
	MOC_DIR     = ../../../obj/tests/test_textparser/debug
	RCC_DIR     = ../../../obj/tests/test_textparser/debug
	UI_DIR      = ../../../obj/tests/test_textparser/debug
}
release {
	OBJECTS_DIR = ../../../obj/tests/test_textparser/release
	MOC_DIR     = ../../../obj/tests/test_textparser/release
	RCC_DIR     = ../../../obj/tests/test_textparser/release
	UI_DIR      = ../../../obj/tests/test_textparser/release
}

DEPENDPATH  += . ../../textparser
INCLUDEPATH += . ../../textparser

SOURCES += main.cpp ../../textparser/qtextparser.cpp
HEADERS +=          ../../textparser/qtextparser.h
