lessThan(QT_MAJOR_VERSION, 6) {
    error("Unsupported Qt version(Needs Qt6).")
}

TEMPLATE       = subdirs
CONFIG        += debug_and_release c++11
SUBDIRS        = appserver mkfusion_generator mkfusion_worker mod_mkfusion
