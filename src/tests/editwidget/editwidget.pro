lessThan(QT_MAJOR_VERSION, 6) {
    error("Unsupported Qt version(Needs Qt6).")
}

QT       = core gui widgets xml core5compat

CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

DEPENDPATH  += . ../../cfeditor/codeeditwidget ../../textparser
INCLUDEPATH += . ../../cfeditor/codeeditwidget ../../textparser

SOURCES = main.cpp qappmaindialog.cpp ../../cfeditor/codeeditwidget/qcodeeditwidget.cpp
HEADERS =          qappmaindialog.h   ../../cfeditor/codeeditwidget/qcodeeditwidget.h
FORMS   =          qappmaindialog.ui

SOURCES += ../../textparser/qtextparser.cpp
HEADERS += ../../textparser/qtextparser.h   ../../textparser/qtextparserelement.h   ../../textparser/qtextparserline.h   ../../textparser/qtextparserlanguagedefinitiontoken.h   ../../textparser/qtextparserlanguagedefinition.h
