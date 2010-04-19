TARGET = editwidget
CONFIG -= app_bundle
TEMPLATE = app
DESTDIR = ../../../bin
OBJECTS_DIR = ../../../obj/editwidget_debug
MOC_DIR = ../../../obj/editwidget_debug
RCC_DIR =  ../../../obj/editwidget_debug
UI_DIR =  ../../../obj/editwidget_debug
DEPENDPATH += . ../../cfeditor/codeeditwidget
INCLUDEPATH += . ../../cfeditor/codeeditwidget

HEADERS +=          qappmaindialog.h   qcodeeditwidget.h
SOURCES += main.cpp qappmaindialog.cpp qcodeeditwidget.cpp
FORMS   += qappmaindialog.ui
