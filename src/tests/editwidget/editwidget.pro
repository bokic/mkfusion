QT       = core gui xml
CONFIG  += debug_and_release
#MAKEFILE = ../../../obj/tests/editwidget/Makefile
DESTDIR  = ../../../bin

debug {
	OBJECTS_DIR = ../../../obj/tests/editwidget/debug
	MOC_DIR     = ../../../obj/tests/editwidget/debug
	RCC_DIR     = ../../../obj/tests/editwidget/debug
	UI_DIR      = ../../../obj/tests/editwidget/debug
}
release {
	OBJECTS_DIR = ../../../obj/tests/editwidget/release
	MOC_DIR     = ../../../obj/tests/editwidget/release
	RCC_DIR     = ../../../obj/tests/editwidget/release
	UI_DIR      = ../../../obj/tests/editwidget/release
}

DEPENDPATH  += . ../../cfeditor/codeeditwidget ../../textparser
INCLUDEPATH += . ../../cfeditor/codeeditwidget ../../textparser

SOURCES = main.cpp qappmaindialog.cpp qcodeeditwidget.cpp ../../textparser/qtextparser.cpp
HEADERS =          qappmaindialog.h   qcodeeditwidget.h   ../../textparser/qtextparser.h
FORMS   =          qappmaindialog.ui
