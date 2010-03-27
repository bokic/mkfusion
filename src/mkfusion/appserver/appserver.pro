TEMPLATE = app
TARGET = mkfusion
QT -= gui
QT += network \
    sql \
    xml

DESTDIR = ../../../bin
DEPENDPATH +=  . ../../../libs/qtservice ../../cfparser
INCLUDEPATH += . ../../../libs/qtservice ../../cfparser

win32:QMAKE_LFLAGS += -Wl,--out-implib,lib/mkfusion.a
unix:QMAKE_LFLAGS += -Wl,-E

SOURCES += \
	main.cpp \
	../../../libs/qtservice/qtservice.cpp \
	../../cfparser/qcffunction.cpp \
	../../cfparser/qcfparser.cpp \
	../../cfparser/qcftag.cpp \
	../../cfparser/qcf8.cpp \
	qmkfusionexception.cpp \
	qcfrunningtemplate.cpp \
	qcfgenerator.cpp \
    cffunctions.cpp \
    qcftemplate.cpp \
    qcfserver.cpp \
    common.cpp \
	qwddx.cpp
win32:SOURCES += \
	../../../libs/qtservice/qtservice_win.cpp
unix:SOURCES += \
	../../../libs/qtservice/qtservice_unix.cpp \
	../../../libs/qtservice/qtunixsocket.cpp \
	../../../libs/qtservice/qtunixserversocket.cpp

HEADERS += \
	../../../libs/qtservice/qtservice_p.h \
	../../../libs/qtservice/qtservice.h \
	../../cfparser/qcfparser.h \
	../../cfparser/qcftag.h \
	../../cfparser/qcffunction.h \
	../../cfparser/qcf8.h \
	qcfgenerator.h \
    cffunctions.h \
    qcftemplate.h \
    qcfserver.h \
    common.h \
    qwddx.h \
    qmkfusionexception.h \
    qcfrunningtemplate.h \
    cftags.h
unix:HEADERS += \
	../../../libs/qtservice/qtunixsocket.h \
	../../../libs/qtservice/qtunixserversocket.h
