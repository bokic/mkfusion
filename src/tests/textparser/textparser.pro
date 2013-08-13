lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       += core xml
CONFIG   += debug_and_release c++11
DESTDIR   = ../../../bin

DEFINES  += DEBUG_QTEXTPARSER

debug {
	OBJECTS_DIR = ../../../obj/tests/test_textparser/debug
	MOC_DIR     = ../../../obj/tests/test_textparser/debug
	RCC_DIR     = ../../../obj/tests/test_textparser/debug
	UI_DIR      = ../../../obj/tests/test_textparser/debug
}
release {
	OBJECTS_DIR = ../../../obj/tests/test_textparser/release
	MOC_DIR     = ../../../obj/tests/test_textparser/release
	RCC_DIR     = ../../../obj/tests/test_textparser/release
	UI_DIR      = ../../../obj/tests/test_textparser/release
}

DEPENDPATH  += . ../../textparser
INCLUDEPATH += . ../../textparser

SOURCES += main.cpp ../../textparser/qtextparser.cpp
HEADERS +=          ../../textparser/qtextparser.h
