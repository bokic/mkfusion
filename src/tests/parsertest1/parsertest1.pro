lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core gui widgets

CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

DEPENDPATH  += . ../../cfparser ../../mkfusion/appserver
INCLUDEPATH += . ../../cfparser ../../mkfusion/appserver

SOURCES     = main.cpp parsertest1.cpp qdetail.cpp ../../cfparser/qcfparser.cpp ../../cfparser/qcffunction.cpp ../../cfparser/qcftag.cpp ../../cfparser/qcf8.cpp
HEADERS     =          parsertest1.h   qdetail.h   ../../cfparser/qcfparser.h   ../../cfparser/qcffunction.h   ../../cfparser/qcftag.h   ../../cfparser/qcf8.h
FORMS       =          parsertest1.ui  qdetail.ui
