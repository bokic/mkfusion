lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core
CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

DEPENDPATH  += . ../../../libs/libssh/include
INCLUDEPATH += . ../../../libs/libssh/include

SOURCES += main.cpp

win32:LIBS += ../../../libs/libssh/lib/libssh.dll.a
unix:LIBS += -lssh
