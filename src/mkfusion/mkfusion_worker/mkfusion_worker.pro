lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

TEMPLATE  = app
QT        = core
CONFIG   += debug_and_release c++11
TARGET    = mkfusion_worker
DESTDIR   = ../../../bin

# Input
SOURCES   = main.cpp

