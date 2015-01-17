lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core gui widgets xml

CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

DEFINES  += DEBUG_QTEXTPARSER

DEPENDPATH  += . ../../textparser ../../cfparser ../../mkfusion/appserver
INCLUDEPATH += . ../../textparser ../../cfparser ../../mkfusion/appserver

SOURCES     = main.cpp parsertest1.cpp qdetail.cpp ../../textparser/qtextparsercompat.cpp ../../cfparser/qcfparser.cpp ../../cfparser/qcffunction.cpp ../../cfparser/qcftag.cpp ../../cfparser/qcf8.cpp
HEADERS     =          parsertest1.h   qdetail.h   ../../textparser/qtextparsercompat.h ../../cfparser/qcfparser.h   ../../cfparser/qcffunction.h   ../../cfparser/qcftag.h   ../../cfparser/qcf8.h
FORMS       =          parsertest1.ui  qdetail.ui

SOURCES += ../../textparser/qtextparser.cpp ../../textparser/qtextparserelement.cpp ../../textparser/qtextparserline.cpp ../../textparser/qtextparserlanguagedefinitiontoken.cpp
HEADERS += ../../textparser/qtextparser.h   ../../textparser/qtextparserelement.h   ../../textparser/qtextparserline.h   ../../textparser/qtextparserlanguagedefinitiontoken.h
