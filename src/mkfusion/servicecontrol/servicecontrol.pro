lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

QT       =
CONFIG  += debug_and_release c++11
DESTDIR  = ../../../WINDOWS

debug {
	OBJECTS_DIR = ../../../obj/mkfusion/servicecontrol/debug
	MOC_DIR     = ../../../obj/mkfusion/servicecontrol/debug
	RCC_DIR     = ../../../obj/mkfusion/servicecontrol/debug
	UI_DIR      = ../../../obj/mkfusion/servicecontrol/debug
}
release {
	OBJECTS_DIR = ../../../obj/mkfusion/servicecontrol/release
	MOC_DIR     = ../../../obj/mkfusion/servicecontrol/release
	RCC_DIR     = ../../../obj/mkfusion/servicecontrol/release
	UI_DIR      = ../../../obj/mkfusion/servicecontrol/release
}

DEPENDPATH  += .
INCLUDEPATH += .

SOURCES = main.cpp
