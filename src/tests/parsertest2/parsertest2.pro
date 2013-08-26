lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core network sql concurrent testlib
CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

debug {
	OBJECTS_DIR = ../../../obj/tests/parsertest2/debug
	MOC_DIR     = ../../../obj/tests/parsertest2/debug
	RCC_DIR     = ../../../obj/tests/parsertest2/debug
	UI_DIR      = ../../../obj/tests/parsertest2/debug
}
release {
	OBJECTS_DIR = ../../../obj/tests/parsertest2/release
	MOC_DIR     = ../../../obj/tests/parsertest2/release
	RCC_DIR     = ../../../obj/tests/parsertest2/release
	UI_DIR      = ../../../obj/tests/parsertest2/release
}

DEPENDPATH  += . ../../cfparser ../../mkfusion/appserver
INCLUDEPATH += . ../../cfparser ../../mkfusion/appserver

win32:LIBS += -ladvapi32

SOURCES = main.cpp ../../mkfusion/appserver/common.cpp ../../mkfusion/appserver/qwddx.cpp ../../mkfusion/appserver/qcfserver.cpp ../../mkfusion/appserver/qcfrunningtemplate.cpp ../../mkfusion/appserver/qcfgenerator.cpp ../../mkfusion/appserver/cffunctions.cpp ../../cfparser/qcfparser.cpp ../../cfparser/qcf8.cpp ../../cfparser/qcftag.cpp ../../cfparser/qcffunction.cpp
HEADERS =          ../../mkfusion/appserver/common.h   ../../mkfusion/appserver/qwddx.h   ../../mkfusion/appserver/qcfserver.h   ../../mkfusion/appserver/qcfrunningtemplate.h   ../../mkfusion/appserver/qcfgenerator.h   ../../mkfusion/appserver/cffunctions.h   ../../cfparser/qcfparser.h   ../../cfparser/qcf8.h   ../../cfparser/qcftag.h   ../../cfparser/qcffunction.h
