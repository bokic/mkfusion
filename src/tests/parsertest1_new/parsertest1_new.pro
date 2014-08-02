lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core gui widgets xml

CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

DEFINES  += DEBUG_QTEXTPARSER

DEPENDPATH  = . ../../textparser/
INCLUDEPATH = . ../../textparser/

SOURCES     = main.cpp parsertest1_new.cpp qdetail.cpp ../../textparser/qtextparser.cpp
HEADERS     =          parsertest1_new.h   qdetail.h   ../../textparser/qtextparser.h
FORMS       =          parsertest1_new.ui  qdetail.ui
