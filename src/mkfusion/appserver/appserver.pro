lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       = core network sql concurrent xml
CONFIG  += debug_and_release c++11
TARGET   = mkfusion
DESTDIR  = ../../../bin

DEPENDPATH  += . ../../../libs/qtservice ../../cfparser qwddx
INCLUDEPATH += . ../../../libs/qtservice ../../cfparser qwddx

# main app
SOURCES  = main.cpp qmkfusionservice.cpp qcfserver.cpp qcfapplicationmanager.cpp qcfsessionmanager.cpp qcfdatabasepoolmanager.cpp qcfworkersmanager.cpp qcfsettingsmanager.cpp qcfschedulerthread.cpp qcflog.cpp qcfsettings.cpp qcfworkerthread.cpp qcfdatabaseconnection.cpp
HEADERS  =          qmkfusionservice.h   qcfserver.h    qcfapplicationmanager.h  qcfsessionmanager.h   qcfdatabasepoolmanager.h   qcfworkersmanager.h   qcfsettingsmanager.h   qcfschedulerthread.h   qcflog.h   qcfsettings.h   qcfworkerthread.h   qcfdatabaseconnection.h

HEADERS += qcfsession.h qmkfusionexception.h

SOURCES += qwddx/qwddx.cpp qwddx/qwddxargument.cpp qwddx/qwddxcomponent.cpp qwddx/qwddxfunction.cpp
HEADERS += qwddx/qwddx.h   qwddx/qwddxargument.h   qwddx/qwddxcomponent.h   qwddx/qwddxfunction.h

# QtService
SOURCES       += ../../../libs/qtservice/qtservice.cpp
win32:SOURCES += ../../../libs/qtservice/qtservice_win.cpp
unix:SOURCES  += ../../../libs/qtservice/qtservice_unix.cpp ../../../libs/qtservice/qtunixsocket.cpp ../../../libs/qtservice/qtunixserversocket.cpp
unix:HEADERS  +=                                            ../../../libs/qtservice/qtunixsocket.h   ../../../libs/qtservice/qtunixserversocket.h

QMAKE_CXXFLAGS += -Wno-unused-parameter

win32:QMAKE_LFLAGS += -Wl,--out-implib,../../../lib/mkfusion.a
unix:QMAKE_LFLAGS += -Wl,-E
