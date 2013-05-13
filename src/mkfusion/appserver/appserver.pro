QT       = core network sql concurrent xml
CONFIG  += debug_and_release
TARGET   = mkfusion
DESTDIR  = ../../../bin

debug {
	OBJECTS_DIR = ../../../obj/mkfusion/appserver/debug
	MOC_DIR     = ../../../obj/mkfusion/appserver/debug
	RCC_DIR     = ../../../obj/mkfusion/appserver/debug
	UI_DIR      = ../../../obj/mkfusion/appserver/debug
}
release {
	OBJECTS_DIR = ../../../obj/mkfusion/appserver/release
	MOC_DIR     = ../../../obj/mkfusion/appserver/release
	RCC_DIR     = ../../../obj/mkfusion/appserver/release
	UI_DIR      = ../../../obj/mkfusion/appserver/release
}

DEPENDPATH  += . ../../../libs/qtservice ../../cfparser
INCLUDEPATH += . ../../../libs/qtservice ../../cfparser

# main app
SOURCES = main.cpp ../../cfparser/qcffunction.cpp ../../cfparser/qcfparser.cpp ../../cfparser/qcftag.cpp ../../cfparser/qcf8.cpp qmkfusionexception.cpp qcfrunningtemplate.cpp qcfgenerator.cpp cffunctions.cpp qcftemplate.cpp qcfserver.cpp common.cpp qwddx.cpp
HEADERS =          ../../cfparser/qcffunction.h   ../../cfparser/qcfparser.h   ../../cfparser/qcftag.h   ../../cfparser/qcf8.h   qmkfusionexception.h   qcfrunningtemplate.h   qcfgenerator.h   cffunctions.h   qcftemplate.h   qcfserver.h   common.h   qwddx.h   cftags.h

# QtService
SOURCES       += ../../../libs/qtservice/qtservice.cpp
win32:SOURCES += ../../../libs/qtservice/qtservice_win.cpp
unix:SOURCES  += ../../../libs/qtservice/qtservice_unix.cpp ../../../libs/qtservice/qtunixsocket.cpp ../../../libs/qtservice/qtunixserversocket.cpp
unix:HEADERS +=                                             ../../../libs/qtservice/qtunixsocket.h   ../../../libs/qtservice/qtunixserversocket.h

win32:QMAKE_LFLAGS += -Wl,--out-implib,../../../lib/mkfusion.a
unix:QMAKE_LFLAGS += -Wl,-E
