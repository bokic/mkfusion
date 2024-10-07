lessThan(QT_MAJOR_VERSION, 6) {
    error("Unsupported Qt version(Needs Qt6).")
}

CONFIG  += debug_and_release c++11

DEPENDPATH  += . ../../mkfusion/simplifiedlocalsocket/
INCLUDEPATH += . ../../mkfusion/simplifiedlocalsocket/

SOURCES = main.cpp
SOURCES  += ../../mkfusion/simplifiedlocalsocket/qsimplifiedlocalsocket_unix.cpp
HEADERS        = ../../mkfusion/simplifiedlocalsocket/qsimplifiedlocalsocket.h
