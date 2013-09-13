lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       =
CONFIG  += debug_and_release c++11
DESTDIR  = ../../../WINDOWS

DEPENDPATH  += .
INCLUDEPATH += .

SOURCES = main.cpp
