cmake_minimum_required(VERSION 3.5)

project(cfeditor VERSION 0.5 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)

find_package(QT NAMES Qt6 COMPONENTS Core Gui Network Xml Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Network Xml Widgets REQUIRED)

include_directories(
    .
    codeeditwidget
    rds
    ../textparser
)

include_directories(${Qt6Core_INCLUDE_DIRS} ${Qt6Network_INCLUDE_DIRS} ${Qt6Xml_INCLUDE_DIRS} ${Qt6Widgets_INCLUDE_DIRS})

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

target_link_libraries(cfeditor PRIVATE Qt6::Core Qt6::Network Qt6::Xml Qt6::Widgets -lssh)
