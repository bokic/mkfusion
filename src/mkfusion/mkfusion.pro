TEMPLATE       = subdirs
CONFIG        += debug_and_release
SUBDIRS        = appserver mod_mkfusion
win32:SUBDIRS += mkfusion_isapi servicecontrol uninstall
#MAKEFILE       = ../../obj/mkfusion/Makefile
