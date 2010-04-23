TEMPLATE = subdirs

SUBDIRS += appserver mod_mkfusion
win32:SUBDIRS += mkfusion_isapi servicecontrol uninstall
