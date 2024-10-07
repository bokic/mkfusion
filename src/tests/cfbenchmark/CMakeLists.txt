cmake_minimum_required(VERSION 3.5)

project(cfbenchmark VERSION 0.5 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)

find_package(QT NAMES Qt6 COMPONENTS Core Network Sql Xml Concurrent Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network Sql Xml Concurrent Test REQUIRED)

include_directories(
    .
    ../../cfparser
    ../../textparser
    ../../mkfusion/appserver
    ../../mkfusion/appserver/qcfvariant
    ../../../libs/qtservice
    ../../mkfusion/mkfusion_generator
)

add_executable(cfbenchmark
    main.cpp

    ../../mkfusion/appserver/qcfvariant/qcfvariant.cpp
    ../../mkfusion/appserver/qcfvariant/qcfvariantcomponent.cpp
    ../../mkfusion/appserver/qcfvariant/qcfvariantfunction.cpp
    ../../mkfusion/appserver/qcfvariant/qcfvariantargument.cpp
    ../../mkfusion/appserver/qcfserver.cpp
    ../../mkfusion/appserver/qcfworkerthread.cpp
    ../../mkfusion/appserver/qcfschedulerthread.cpp
    ../../mkfusion/appserver/qcfapplicationmanager.cpp
    ../../mkfusion/appserver/qcfsessionmanager.cpp
    ../../mkfusion/appserver/qcfdatabasepoolmanager.cpp
    ../../mkfusion/appserver/qcfdatabaseconnection.cpp
    ../../mkfusion/appserver/qcfworkersmanager.cpp
    ../../mkfusion/appserver/qcftemplatesmanager.cpp
    ../../mkfusion/appserver/qcfsettingsmanager.cpp
    ../../mkfusion/appserver/qcfsettings.cpp
    ../../mkfusion/appserver/qcflog.cpp
    ../../mkfusion/appserver/qcftemplate.cpp
    ../../mkfusion/appserver/qcftemplateinfo.cpp
    ../../mkfusion/mkfusion_generator/qcfgenerator.cpp
    ../../mkfusion/appserver/cffunctions.cpp
    ../../mkfusion/appserver/qhttpcodec.cpp
    ../../cfparser/qcfparser.cpp
    ../../cfparser/qcf8.cpp
    ../../cfparser/qcftag.cpp
    ../../cfparser/qcffunction.cpp
    ../../mkfusion/appserver/qcfcompiler.cpp
    ../../mkfusion/mkfusion_generator/qcftemplategenerator.cpp
    ../../mkfusion/mkfusion_generator/qcfcomponentgenerator.cpp

    ../../mkfusion/appserver/qcfapplication.cpp

    ../../textparser/qtextparser.cpp
)

target_link_libraries(cfbenchmark PRIVATE Qt6::Core Qt6::Network Qt6::Sql Qt6::Xml Qt6::Test)
