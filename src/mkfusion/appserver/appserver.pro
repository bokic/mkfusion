lessThan(QT_MAJOR_VERSION, 6) {
    error("Unsupported Qt version(Needs Qt6).")
}

QT       = core network sql xml
CONFIG  += debug_and_release c++11
TARGET   = mkfusion
DESTDIR  = ../../../bin

GIT_DESCRIBE = $$system(git describe)
DEFINES += BUILDNUMBER=\\\"$$GIT_DESCRIBE\\\"

DEPENDPATH  += . ../../../libs/qtservice ../../cfparser qcfvariant
INCLUDEPATH += . ../../../libs/qtservice ../../cfparser qcfvariant

# main app
SOURCES  = main.cpp qmkfusionservice.cpp qcfserver.cpp  qhttpcodec.cpp qcfcompiler.cpp qcfapplicationmanager.cpp qcfsessionmanager.cpp qcfdatabasepoolmanager.cpp qcfworkersmanager.cpp qcfsettingsmanager.cpp qcfschedulerthread.cpp qcflog.cpp qcfsettings.cpp qcfworkerthread.cpp qcfdatabaseconnection.cpp qcftemplatesmanager.cpp qcftemplate.cpp qcftemplateinfo.cpp
HEADERS  =          qmkfusionservice.h   qcfserver.h    qhttpcodec.h   qcfcompiler.h   qcfapplicationmanager.h   qcfsessionmanager.h   qcfdatabasepoolmanager.h   qcfworkersmanager.h   qcfsettingsmanager.h   qcfschedulerthread.h   qcflog.h   qcfsettings.h   qcfworkerthread.h   qcfdatabaseconnection.h   qcftemplatesmanager.h   qcftemplate.h   qcftemplateinfo.h

SOURCES += qcfapplication.cpp
HEADERS += qcfapplication.h   qcfsession.h qmkfusionexception.h

SOURCES += qcfvariant/qcfvariant.cpp qcfvariant/qcfvariantargument.cpp qcfvariant/qcfvariantcomponent.cpp qcfvariant/qcfvariantfunction.cpp
HEADERS += qcfvariant/qcfvariant.h   qcfvariant/qcfvariantargument.h   qcfvariant/qcfvariantcomponent.h   qcfvariant/qcfvariantfunction.h

SOURCES += cffunctions.cpp
HEADERS += cffunctions.h

# QtService
SOURCES  += ../../../libs/qtservice/qtservice.cpp
SOURCES  += ../../../libs/qtservice/qtservice_unix.cpp ../../../libs/qtservice/qtunixsocket.cpp ../../../libs/qtservice/qtunixserversocket.cpp
HEADERS  +=                                            ../../../libs/qtservice/qtunixsocket.h   ../../../libs/qtservice/qtunixserversocket.h

QMAKE_LFLAGS += -Wl,-E
