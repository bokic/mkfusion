cmake_minimum_required(VERSION 3.5)

project(cf7debugger VERSION 0.5 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)

find_package(QT NAMES Qt6 COMPONENTS Core Network Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network Widgets REQUIRED)

include_directories( . )

add_executable(cf7debugger
    main.cpp qjdwpsocket.cpp qjdwpdebugger.cpp qappmainwindow.cpp qjdwpcommand.cpp qjdwpgetpathseparatorcommand.cpp qjdwpclassesbysignaturecommand.cpp qjdwpidsizescommand.cpp
             qjdwpsocket.h   qjdwpdebugger.h   qappmainwindow.h   qjdwpcommand.h   qjdwpgetpathseparatorcommand.h   qjdwpclassesbysignaturecommand.h   qjdwpidsizescommand.h
)

target_link_libraries(cf7debugger PRIVATE Qt6::Core Qt6::Network Qt6::Widgets)
