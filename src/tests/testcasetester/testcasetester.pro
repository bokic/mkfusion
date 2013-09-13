lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core gui widgets network

CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

DEPENDPATH  += .
INCLUDEPATH += .

FORMS   =          maindialog.ui  comparedialog.ui
SOURCES = main.cpp maindialog.cpp comparedialog.cpp
HEADERS =          maindialog.h   comparedialog.h
