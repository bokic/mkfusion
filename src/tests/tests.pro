lessThan(QT_MAJOR_VERSION, 6) {
    error("Unsupported Qt version(Needs Qt6).")
}

TEMPLATE = subdirs
CONFIG  += debug_and_release c++11
SUBDIRS  = cfbenchmark cf7debugger parsertest1_old parsertest1_new parsertest2 textparser testcasetester
