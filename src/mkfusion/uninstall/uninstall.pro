lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

TEMPLATE = lib
QT       =
CONFIG  += debug_and_release c++11
DESTDIR  = ../../../install/windows

debug {
	OBJECTS_DIR = ../../../obj/mkfusion/uninstall/debug
	MOC_DIR     = ../../../obj/mkfusion/uninstall/debug
	RCC_DIR     = ../../../obj/mkfusion/uninstall/debug
	UI_DIR      = ../../../obj/mkfusion/uninstall/debug
}
release {
        OBJECTS_DIR = ../../../obj/mkfusion/uninstall/release
        MOC_DIR     = ../../../obj/mkfusion/uninstall/release
        RCC_DIR     = ../../../obj/mkfusion/uninstall/release
        UI_DIR      = ../../../obj/mkfusion/uninstall/release
}

DEPENDPATH  += .
INCLUDEPATH += .

LIBS   += -static-libgcc -static-libstdc++

SOURCES = uninstall.cpp
HEADERS = uninstall.h
