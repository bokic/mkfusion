lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

TEMPLATE       = subdirs
CONFIG        += debug_and_release c++11
SUBDIRS        = appserver mkfusion_generator mkfusion_worker #mod_mkfusion
win32:SUBDIRS += uninstall
