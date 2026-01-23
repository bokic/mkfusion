cmake_minimum_required(VERSION 3.5)

project(appserver VERSION 0.5 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}../../../bin)

include_directories(
    .
    ../../../libs/qtservice
    ../../cfparser
    qcfvariant
)

find_package(QT NAMES Qt6 COMPONENTS Core Network Sql Xml Core5Compat REQUIRED)
find_package(Qt6 COMPONENTS Core Network Sql Xml Core5Compat REQUIRED)

IF (WIN32)
set(QTSERVICE_HEADERS
)
set(QTSERVICE_SOURCES
    ../../../libs/qtservice/qtservice_win.cpp
)
ELSE()
set(QTSERVICE_HEADERS
    ../../../libs/qtservice/qtunixsocket.h
    ../../../libs/qtservice/qtunixserversocket.h
)
set(QTSERVICE_SOURCES
    ../../../libs/qtservice/qtservice.cpp
    ../../../libs/qtservice/qtservice_unix.cpp
    ../../../libs/qtservice/qtunixsocket.cpp
    ../../../libs/qtservice/qtunixserversocket.cpp
)
ENDIF()

set(PROJECT_HEADERS
    qmkfusionservice.h
    qcfserver.h
    qhttpcodec.h
    qcfcompiler.h
    qcfapplicationmanager.h
    qcfsessionmanager.h
    qcfdatabasepoolmanager.h
    qcfworkersmanager.h
    qcfsettingsmanager.h
    qcfschedulerthread.h
    qcflog.h
    qcfsettings.h
    qcfworkerthread.h
    qcfdatabaseconnection.h
    qcftemplatesmanager.h
    qcftemplate.h
    qcftemplateinfo.h

    qcfapplication.h
    qcfsession.h
    qmkfusionexception.h

    qcfvariant/qcfvariant.h
    qcfvariant/qcfvariantargument.h
    qcfvariant/qcfvariantcomponent.h
    qcfvariant/qcfvariantfunction.h

    cffunctions.h

    ${QTSERVICE_HEADERS}
)

set(PROJECT_SOURCES
    main.cpp
    qmkfusionservice.cpp
    qcfserver.cpp
    qhttpcodec.cpp
    qcfcompiler.cpp
    qcfapplicationmanager.cpp
    qcfsessionmanager.cpp
    qcfdatabasepoolmanager.cpp
    qcfworkersmanager.cpp
    qcfsettingsmanager.cpp
    qcfschedulerthread.cpp
    qcflog.cpp
    qcfsettings.cpp
    qcfworkerthread.cpp
    qcfdatabaseconnection.cpp
    qcftemplatesmanager.cpp
    qcftemplate.cpp
    qcftemplateinfo.cpp

    qcfapplication.cpp

    qcfvariant/qcfvariant.cpp
    qcfvariant/qcfvariantargument.cpp
    qcfvariant/qcfvariantcomponent.cpp
    qcfvariant/qcfvariantfunction.cpp

    cffunctions.cpp

    ${QTSERVICE_SOURCES}

    ${PROJECT_HEADERS}
)

add_executable(appserver
    ${PROJECT_SOURCES}
)

#win32:QMAKE_LFLAGS += -Wl,--out-implib,../../../lib/mkfusion.a
#unix:QMAKE_LFLAGS += -Wl,-E

target_link_libraries(appserver PRIVATE Qt6::Core Qt6::Network Qt6::Sql Qt6::Xml Qt6::Core5Compat)
