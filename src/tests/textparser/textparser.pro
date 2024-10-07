lessThan(QT_MAJOR_VERSION, 6) {
    error("Unsupported Qt version(Needs Qt6).")
}

QT       += core xml core5compat
CONFIG   += debug_and_release c++11
DESTDIR   = ../../../bin

DEFINES  += DEBUG_QTEXTPARSER

DEPENDPATH  += . ../../textparser
INCLUDEPATH += . ../../textparser

SOURCES += main.cpp

SOURCES += ../../textparser/qtextparser.cpp
HEADERS += ../../textparser/qtextparser.h   ../../textparser/qtextparserelement.h   ../../textparser/qtextparserline.h   ../../textparser/qtextparserlanguagedefinitiontoken.h   ../../textparser/qtextparserlanguagedefinition.h
