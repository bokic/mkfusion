TEMPLATE = app
TARGET = sftptest
QT -= gui

DESTDIR = ../../../bin
OBJECTS_DIR = ../../../obj/sftptest_debug
MOC_DIR = ../../../obj/sftptest_debug
RCC_DIR =  ../../../obj/sftptest_debug
UI_DIR =  ../../../obj/sftptest_debug
DEPENDPATH += . ../../../libs/libssh/include
INCLUDEPATH += . ../../../libs/libssh/include

# Input
SOURCES += main.cpp

INCLUDEPATH += ../../../libs/libssh/include
win32:LIBS += ../../../libs/libssh/lib/libssh.dll.a
unix:LIBS += /usr/lib/libssh.so
