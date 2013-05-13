QT       = core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += debug_and_release
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

SOURCES = main.cpp qappmaindialog.cpp ../../cfeditor/codeeditwidget/qcodeeditwidget.cpp ../../textparser/qtextparser.cpp
HEADERS =          qappmaindialog.h   ../../cfeditor/codeeditwidget/qcodeeditwidget.h   ../../textparser/qtextparser.h
FORMS   =          qappmaindialog.ui
