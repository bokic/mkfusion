lessThan(QT_MAJOR_VERSION, 6) {
    error("Unsupported Qt version(Needs Qt6).")
}

QT       = core gui widgets xml

CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

DEFINES  += DEBUG_QTEXTPARSER

DEPENDPATH  = . ../../textparser/
INCLUDEPATH = . ../../textparser/

SOURCES     = main.cpp parsertest1.cpp qdetail.cpp
HEADERS     =          parsertest1.h   qdetail.h
FORMS       =          parsertest1.ui  qdetail.ui

SOURCES += ../../textparser/qtextparser.cpp
HEADERS += ../../textparser/qtextparser.h   ../../textparser/qtextparserelement.h   ../../textparser/qtextparserline.h   ../../textparser/qtextparserlanguagedefinitiontoken.h   ../../textparser/qtextparserlanguagedefinition.h
