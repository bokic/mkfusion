lessThan(QT_MAJOR_VERSION, 5) {
    error("Unsupported Qt version(Needs Qt5).")
}

TEMPLATE = subdirs
CONFIG  += debug_and_release c++11
SUBDIRS  = cfbenchmark cf7debugger editwidget parsertest1 parsertest2 rdstest sftptest textparser testcasetester
