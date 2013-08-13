lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core
CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

debug {
	OBJECTS_DIR = ../../../obj/tests/sftptest/debug
	MOC_DIR     = ../../../obj/tests/sftptest/debug
	RCC_DIR     = ../../../obj/tests/sftptest/debug
	UI_DIR      = ../../../obj/tests/sftptest/debug
}
release {
	OBJECTS_DIR = ../../../obj/tests/sftptest/release
	MOC_DIR     = ../../../obj/tests/sftptest/release
	RCC_DIR     = ../../../obj/tests/sftptest/release
	UI_DIR      = ../../../obj/tests/sftptest/release
}

DEPENDPATH  += . ../../../libs/libssh/include
INCLUDEPATH += . ../../../libs/libssh/include

SOURCES += main.cpp

win32:LIBS += ../../../libs/libssh/lib/libssh.dll.a
unix:LIBS += -lssh
