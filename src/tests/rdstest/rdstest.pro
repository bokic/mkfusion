lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core network xml testlib
CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

DEPENDPATH  += . ../../cfeditor/rds/
INCLUDEPATH += . ../../cfeditor/rds/

SOURCES = main.cpp ../../cfeditor/rds/qabstractrdsservice.cpp ../../cfeditor/rds/qdatabaseservice.cpp ../../cfeditor/rds/qdebuggerservice.cpp ../../cfeditor/rds/qfileioservice.cpp ../../cfeditor/rds/qrdsserver.cpp ../../cfeditor/rds/qwddxutils.cpp ../../cfeditor/rds/qcfdebugger.cpp ../../cfeditor/rds/qdefaultservice.cpp ../../cfeditor/rds/qwddx.cpp
HEADERS =          ../../cfeditor/rds/qabstractrdsservice.h   ../../cfeditor/rds/qdatabaseservice.h   ../../cfeditor/rds/qdebuggerservice.h   ../../cfeditor/rds/qfileioservice.h   ../../cfeditor/rds/qrdsserver.h   ../../cfeditor/rds/qwddxutils.h   ../../cfeditor/rds/qcfdebugger.h   ../../cfeditor/rds/qdefaultservice.h   ../../cfeditor/rds/qwddx.h
