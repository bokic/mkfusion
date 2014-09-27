lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core network sql concurrent xml
CONFIG  += debug_and_release c++11
TARGET   = mkfusion
DESTDIR  = ../../../bin

GIT_DESCRIBE = $$system(git describe)
DEFINES += MKFUSION_BUILD_STRING=\\\"$$GIT_DESCRIBE\\\"

DEPENDPATH  += . ../../../libs/qtservice ../../cfparser
INCLUDEPATH += . ../../../libs/qtservice ../../cfparser

# main app
SOURCES = main.cpp qmkfusionservice.cpp ../../cfparser/qcffunction.cpp ../../cfparser/qcfparser.cpp ../../cfparser/qcftag.cpp ../../cfparser/qcf8.cpp qcfapplication.cpp qmkfusionexception.cpp qcfrunningtemplate.cpp qcfgenerator.cpp cffunctions.cpp qcftemplate.cpp qcfserver.cpp common.cpp qwddx.cpp qhttpcodec.cpp
HEADERS =          qmkfusionservice.h   ../../cfparser/qcffunction.h   ../../cfparser/qcfparser.h   ../../cfparser/qcftag.h   ../../cfparser/qcf8.h   qcfapplication.h   qmkfusionexception.h   qcfrunningtemplate.h   qcfgenerator.h   cffunctions.h   qcftemplate.h   qcfserver.h   common.h   qwddx.h   qhttpcodec.h   cftags.h

# QtService
SOURCES       += ../../../libs/qtservice/qtservice.cpp
win32:SOURCES += ../../../libs/qtservice/qtservice_win.cpp
unix:SOURCES  += ../../../libs/qtservice/qtservice_unix.cpp
HEADERS       += ../../../libs/qtservice/qtservice.h        ../../../libs/qtservice/qtservice_p.h

win32:QMAKE_LFLAGS += -Wl,--out-implib,../../../lib/mkfusion.a
unix:QMAKE_LFLAGS += -Wl,-E
