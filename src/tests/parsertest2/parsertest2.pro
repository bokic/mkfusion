lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core network sql concurrent testlib

CONFIG  += debug_and_release c++11
DESTDIR  = ../../../bin

DEPENDPATH  += . ../../cfparser ../../mkfusion/appserver ../../mkfusion/appserver/qcfvariant ../../../libs/qtservice ../../mkfusion/mkfusion_generator
INCLUDEPATH += . ../../cfparser ../../mkfusion/appserver ../../mkfusion/appserver/qcfvariant ../../../libs/qtservice ../../mkfusion/mkfusion_generator

win32:LIBS += -ladvapi32

SOURCES = main.cpp ../../mkfusion/appserver/qcfvariant/qcfvariant.cpp ../../mkfusion/appserver/qcfserver.cpp ../../mkfusion/appserver/qcfworkerthread.cpp ../../mkfusion/appserver/qcfschedulerthread.cpp ../../mkfusion/appserver/qcfapplicationmanager.cpp ../../mkfusion/appserver/qcfsessionmanager.cpp ../../mkfusion/appserver/qcfdatabasepoolmanager.cpp ../../mkfusion/appserver/qcfdatabaseconnection.cpp ../../mkfusion/appserver/qcfworkersmanager.cpp ../../mkfusion/appserver/qcftemplatesmanager.cpp ../../mkfusion/appserver/qcfsettingsmanager.cpp ../../mkfusion/appserver/qcfsettings.cpp ../../mkfusion/appserver/qcflog.cpp ../../mkfusion/appserver/qcftemplate.cpp ../../mkfusion/appserver/qcftemplateinfo.cpp ../../mkfusion/mkfusion_generator/qcfgenerator.cpp ../../mkfusion/appserver/cffunctions.cpp ../../mkfusion/appserver/qhttpcodec.cpp ../../cfparser/qcfparser.cpp ../../cfparser/qcf8.cpp ../../cfparser/qcftag.cpp ../../cfparser/qcffunction.cpp ../../mkfusion/appserver/qcfcompiler.cpp ../../mkfusion/mkfusion_generator/qcftemplategenerator.cpp ../../mkfusion/mkfusion_generator/qcfcomponentgenerator.cpp
HEADERS =          ../../mkfusion/appserver/qcfvariant/qcfvariant.h   ../../mkfusion/appserver/qcfserver.h   ../../mkfusion/appserver/qcfworkerthread.h   ../../mkfusion/appserver/qcfschedulerthread.h   ../../mkfusion/appserver/qcfapplicationmanager.h   ../../mkfusion/appserver/qcfsessionmanager.h   ../../mkfusion/appserver/qcfdatabasepoolmanager.h   ../../mkfusion/appserver/qcfdatabaseconnection.h   ../../mkfusion/appserver/qcfworkersmanager.h   ../../mkfusion/appserver/qcftemplatesmanager.h   ../../mkfusion/appserver/qcfsettingsmanager.h   ../../mkfusion/appserver/qcfsettings.h   ../../mkfusion/appserver/qcflog.h   ../../mkfusion/appserver/qcftemplate.h   ../../mkfusion/appserver/qcftemplateinfo.h   ../../mkfusion/mkfusion_generator/qcfgenerator.h   ../../mkfusion/appserver/cffunctions.h   ../../mkfusion/appserver/qhttpcodec.h   ../../cfparser/qcfparser.h   ../../cfparser/qcf8.h   ../../cfparser/qcftag.h   ../../cfparser/qcffunction.h   ../../mkfusion/appserver/qcfcompiler.h   ../../mkfusion/mkfusion_generator/qcftemplategenerator.h   ../../mkfusion/mkfusion_generator/qcfcomponentgenerator.h

# QtService
SOURCES       += ../../../libs/qtservice/qtservice.cpp
win32:SOURCES += ../../../libs/qtservice/qtservice_win.cpp
unix:SOURCES  += ../../../libs/qtservice/qtservice_unix.cpp ../../../libs/qtservice/qtunixsocket.cpp ../../../libs/qtservice/qtunixserversocket.cpp
unix:HEADERS +=                                             ../../../libs/qtservice/qtunixsocket.h   ../../../libs/qtservice/qtunixserversocket.h

QMAKE_CXXFLAGS += -Wno-unused-parameter
