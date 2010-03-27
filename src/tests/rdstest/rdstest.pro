TEMPLATE = app
TARGET = rdstest

QT -= gui
QT+= network xml

DESTDIR = ../../../bin
OBJECTS_DIR = ../../../obj/rdstest_debug
MOC_DIR = ../../../obj/rdstest_debug
RCC_DIR = ../../../obj/rdstest_debug
UI_DIR =  ../../../obj/rdstest_debug
DEPENDPATH += . ../../cfeditor/rds/
INCLUDEPATH += . ../../cfeditor/rds/

# Input
SOURCES += main.cpp ../../cfeditor/rds/qabstractrdsservice.cpp ../../cfeditor/rds/qdatabaseservice.cpp ../../cfeditor/rds/qdebuggerservice.cpp ../../cfeditor/rds/qfileioservice.cpp ../../cfeditor/rds/qrdsserver.cpp ../../cfeditor/rds/qwddxutils.cpp ../../cfeditor/rds/qcfdebugger.cpp ../../cfeditor/rds/qdefaultservice.cpp ../../cfeditor/rds/qwddx.cpp
HEADERS +=          ../../cfeditor/rds/qabstractrdsservice.h   ../../cfeditor/rds/qdatabaseservice.h   ../../cfeditor/rds/qdebuggerservice.h   ../../cfeditor/rds/qfileioservice.h   ../../cfeditor/rds/qrdsserver.h   ../../cfeditor/rds/qwddxutils.h   ../../cfeditor/rds/qcfdebugger.h   ../../cfeditor/rds/qdefaultservice.h   ../../cfeditor/rds/qwddx.h
