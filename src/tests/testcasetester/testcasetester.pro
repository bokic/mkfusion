QT       = core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += debug_and_release
DESTDIR  = ../../../bin

debug {
	OBJECTS_DIR = ../../../obj/tests/testcasetester/debug
	MOC_DIR     = ../../../obj/tests/testcasetester/debug
	RCC_DIR     = ../../../obj/tests/testcasetester/debug
	UI_DIR      = ../../../obj/tests/testcasetester/debug
}
release {
	OBJECTS_DIR = ../../../obj/tests/testcasetester/release
	MOC_DIR     = ../../../obj/tests/testcasetester/release
	RCC_DIR     = ../../../obj/tests/testcasetester/release
	UI_DIR      = ../../../obj/tests/testcasetester/release
}

DEPENDPATH  += .
INCLUDEPATH += .

FORMS   =          maindialog.ui  comparedialog.ui
SOURCES = main.cpp maindialog.cpp comparedialog.cpp
HEADERS =          maindialog.h   comparedialog.h
