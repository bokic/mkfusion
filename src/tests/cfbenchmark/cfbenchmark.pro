lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core network concurrent testlib
CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

debug {
	OBJECTS_DIR = ../../../obj/tests/cfbenchmark/debug
	MOC_DIR     = ../../../obj/tests/cfbenchmark/debug
	RCC_DIR     = ../../../obj/tests/cfbenchmark/debug
	UI_DIR      = ../../../obj/tests/cfbenchmark/debug
}
release {
	OBJECTS_DIR = ../../../obj/tests/cfbenchmark/release
	MOC_DIR     = ../../../obj/tests/cfbenchmark/release
	RCC_DIR     = ../../../obj/tests/cfbenchmark/release
	UI_DIR      = ../../../obj/tests/cfbenchmark/release
}

DEPENDPATH  += . ../../cfparser ../../mkfusion/appserver
INCLUDEPATH += . ../../cfparser ../../mkfusion/appserver

SOURCES = main.cpp                     ../../mkfusion/appserver/qwddx.cpp ../../mkfusion/appserver/qcfserver.cpp ../../mkfusion/appserver/qcftemplate.cpp ../../mkfusion/appserver/qcfrunningtemplate.cpp ../../mkfusion/appserver/qcfgenerator.cpp ../../mkfusion/appserver/cffunctions.cpp ../../cfparser/qcfparser.cpp ../../cfparser/qcf8.cpp ../../cfparser/qcftag.cpp ../../cfparser/qcffunction.cpp
HEADERS =          pi_orig.h  pi_opt.h ../../mkfusion/appserver/qwddx.h   ../../mkfusion/appserver/qcfserver.h   ../../mkfusion/appserver/qcftemplate.h   ../../mkfusion/appserver/qcfrunningtemplate.h   ../../mkfusion/appserver/qcfgenerator.h   ../../mkfusion/appserver/cffunctions.h   ../../cfparser/qcfparser.h   ../../cfparser/qcf8.h   ../../cfparser/qcftag.h   ../../cfparser/qcffunction.h
