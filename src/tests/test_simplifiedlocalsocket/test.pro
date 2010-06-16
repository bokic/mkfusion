DEPENDPATH  += . ../../mkfusion/simplifiedlocalsocket/
INCLUDEPATH += . ../../mkfusion/simplifiedlocalsocket/

SOURCES = main.cpp
win32:SOURCES += ../../mkfusion/simplifiedlocalsocket/qsimplifiedlocalsocket_win.cpp
unix:SOURCES  += ../../mkfusion/simplifiedlocalsocket/qsimplifiedlocalsocket_unix.cpp
HEADERS        = ../../mkfusion/simplifiedlocalsocket/qsimplifiedlocalsocket.h
