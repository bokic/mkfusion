lessThan(QT_MAJOR_VERSION, 6) {
    error("Unsupported Qt version(Needs Qt6).")
}

QT       = core
CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

DEPENDPATH  += . ../../../libs/libssh/include
INCLUDEPATH += . ../../../libs/libssh/include

SOURCES += main.cpp

LIBS += -lssh
