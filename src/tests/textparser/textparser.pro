lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       += core xml
CONFIG   += debug_and_release c++11
DESTDIR   = ../../../bin

DEFINES  += DEBUG_QTEXTPARSER

DEPENDPATH  += . ../../textparser
INCLUDEPATH += . ../../textparser

SOURCES += main.cpp

SOURCES += ../../textparser/qtextparser.cpp ../../textparser/qtextparserelement.cpp ../../textparser/qtextparserline.cpp ../../textparser/qtextparserlanguagedefinitiontoken.cpp
HEADERS += ../../textparser/qtextparser.h   ../../textparser/qtextparserelement.h   ../../textparser/qtextparserline.h   ../../textparser/qtextparserlanguagedefinitiontoken.h
