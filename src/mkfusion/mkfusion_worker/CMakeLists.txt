cmake_minimum_required(VERSION 3.5)

project(mkfusion_worker VERSION 0.5 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}../../../bin)

find_package(QT NAMES Qt6 COMPONENTS Core Core5Compat REQUIRED)
find_package(Qt6 COMPONENTS Core Core5Compat REQUIRED)

set(PROJECT_SOURCES
    main.cpp
)

add_executable(mkfusion_worker
    ${PROJECT_SOURCES}
)

target_link_libraries(mkfusion_worker PRIVATE Qt6::Core)
