lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

TEMPLATE     = app
QT           = core concurrent
CONFIG      += debug_and_release c++11
TARGET       = mkfusion-generator
DESTDIR      = ../../../bin

DEPENDPATH  += . ../../cfparser
INCLUDEPATH += . ../../cfparser

# Input
SOURCES      = main.cpp

SOURCES     += qcfgenerator.cpp qcftemplategenerator.cpp qcfcomponentgenerator.cpp ../../cfparser/qcfparser.cpp ../../cfparser/qcf8.cpp ../../cfparser/qcffunction.cpp ../../cfparser/qcftag.cpp
HEADERS     += qcfgenerator.h   qcftemplategenerator.h   qcfcomponentgenerator.h   ../../cfparser/qcfparser.h   ../../cfparser/qcf8.h   ../../cfparser/qcffunction.h   ../../cfparser/qcftag.h

HEADERS     += qcfgeneratorexception.h
