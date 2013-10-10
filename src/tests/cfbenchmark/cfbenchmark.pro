lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core network sql concurrent testlib

CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

DEPENDPATH  += . ../../cfparser ../../mkfusion/appserver ../../../libs/qtservice ../../mkfusion/mkfusion_generator
INCLUDEPATH += . ../../cfparser ../../mkfusion/appserver ../../../libs/qtservice ../../mkfusion/mkfusion_generator

SOURCES = main.cpp                     ../../mkfusion/appserver/qcfapplication.cpp ../../mkfusion/appserver/common.cpp ../../mkfusion/appserver/qwddx.cpp ../../mkfusion/appserver/qcfserver.cpp ../../mkfusion/appserver/qcftemplate.cpp ../../mkfusion/appserver/qcfrunningtemplate.cpp ../../mkfusion/mkfusion_generator/qcfgenerator.cpp ../../mkfusion/appserver/cffunctions.cpp ../../mkfusion/appserver/qhttpcodec.cpp ../../cfparser/qcfparser.cpp ../../cfparser/qcf8.cpp ../../cfparser/qcftag.cpp ../../cfparser/qcffunction.cpp \
    ../../mkfusion/appserver/qcfcompiler.cpp \
    ../../mkfusion/mkfusion_generator/qcftemplategenerator.cpp \
    ../../mkfusion/mkfusion_generator/qcfcomponentgenerator.cpp

HEADERS =          pi_orig.h  pi_opt.h ../../mkfusion/appserver/qcfapplication.h   ../../mkfusion/appserver/common.h   ../../mkfusion/appserver/qwddx.h   ../../mkfusion/appserver/qcfserver.h   ../../mkfusion/appserver/qcftemplate.h   ../../mkfusion/appserver/qcfrunningtemplate.h   ../../mkfusion/mkfusion_generator/qcfgenerator.h   ../../mkfusion/appserver/cffunctions.h   ../../mkfusion/appserver/qhttpcodec.h   ../../cfparser/qcfparser.h   ../../cfparser/qcf8.h   ../../cfparser/qcftag.h   ../../cfparser/qcffunction.h \
    ../../mkfusion/appserver/qcfcompiler.h \
    ../../mkfusion/mkfusion_generator/qcftemplategenerator.h \
    ../../mkfusion/mkfusion_generator/qcfcomponentgenerator.h

# QtService
SOURCES       += ../../../libs/qtservice/qtservice.cpp
win32:SOURCES += ../../../libs/qtservice/qtservice_win.cpp
unix:SOURCES  += ../../../libs/qtservice/qtservice_unix.cpp ../../../libs/qtservice/qtunixsocket.cpp ../../../libs/qtservice/qtunixserversocket.cpp
unix:HEADERS +=                                             ../../../libs/qtservice/qtunixsocket.h   ../../../libs/qtservice/qtunixserversocket.h

QMAKE_CXXFLAGS += -Wno-unused-parameter
