cmake_minimum_required(VERSION 3.5)

project(cfeditor VERSION 0.5 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)

find_package(QT NAMES Qt5 COMPONENTS Core Gui Network Xml Widgets WebKit WebKitWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Network Xml Widgets WebKit WebKitWidgets REQUIRED)

include_directories(
    .
    codeeditwidget
    rds
    ../textparser
)

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS} ${Qt5Xml_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5WebKit_INCLUDE_DIRS})

set(PROJECT_SOURCES

    # Main app
    main.cpp qappmainwindow.cpp qprojectproperties.cpp
             qappmainwindow.h   qprojectproperties.h

    # RDS
    rds/qabstractrdsservice.cpp rds/qrdsserver.cpp rds/qdefaultservice.cpp rds/qcfdebugger.cpp rds/qdebuggerservice.cpp rds/qfileioservice.cpp rds/qdatabaseservice.cpp rds/qwddx.cpp rds/qwddxutils.cpp
    rds/qabstractrdsservice.h   rds/qrdsserver.h   rds/qdefaultservice.h   rds/qcfdebugger.h   rds/qdebuggerservice.h   rds/qfileioservice.h   rds/qdatabaseservice.h   rds/qwddx.h   rds/qwddxutils.h

    # Project Loader abstraction and implementation.
    qproject.cpp qlocalproject.cpp qrdsproject.cpp qftpproject.cpp qsftpproject.cpp
    qproject.h   qlocalproject.h   qrdsproject.h   qftpproject.h   qsftpproject.h

    # QProjectFile class(used for sorted display of dirs and files)
    qprojectfile.cpp
    qprojectfile.h

    # QAdvancedTreeWidget(extends QTreeWidget by adding keyPress signal)
    qadvancedtreewidget.cpp
    qadvancedtreewidget.h

    # Custom(QtCreator looklike) edit widget
    codeeditwidget/qcodeeditwidget.cpp
    codeeditwidget/qcodeeditwidget.h

    # TextParser
    ../textparser/qtextparser.cpp
    ../textparser/qtextparser.h   ../textparser/qtextparserelement.h   ../textparser/qtextparserline.h   ../textparser/qtextparserlanguagedefinitiontoken.h   ../textparser/qtextparserlanguagedefinition.h
)

add_executable(cfeditor
    ${PROJECT_SOURCES}
)

target_link_libraries(cfeditor PRIVATE Qt5::Core Qt5::Network Qt5::Xml Qt5::Widgets Qt5::WebKit Qt5::WebKitWidgets -lssh)
