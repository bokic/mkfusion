cmake_minimum_required(VERSION 3.5)

project(mkfusion-generator VERSION 0.5 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}../../../bin)

include_directories(
    ../../cfparser
    ../../cfparser
)

find_package(QT NAMES Qt6 COMPONENTS Core Core5Compat REQUIRED)
find_package(Qt6 COMPONENTS Core Core5Compat REQUIRED)

set(PROJECT_HEADERS
    qcfgenerator.h
    qcftemplategenerator.h
    qcfcomponentgenerator.h
    ../../cfparser/qcfparser.h
    ../../cfparser/qcf8.h
    ../../cfparser/qcffunction.h
    ../../cfparser/qcftag.h

    qcfgeneratorexception.h
)

set(PROJECT_SOURCES
    main.cpp
    qcfgenerator.cpp
    qcftemplategenerator.cpp
    qcfcomponentgenerator.cpp
    ../../cfparser/qcfparser.cpp
    ../../cfparser/qcf8.cpp
    ../../cfparser/qcffunction.cpp
    ../../cfparser/qcftag.cpp
    ${PROJECT_HEADERS}
)

add_executable(mkfusion-generator
    ${PROJECT_SOURCES}
)

target_link_libraries(mkfusion-generator PRIVATE Qt6::Core)
