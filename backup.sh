#!/bin/sh

DATE=`date +%Y%m%d%H%M%S`

# TODO: please set zip command not to delete empty dirs(ex: bin)

zip backup-mkfusion-0.4.1_$DATE.zip * -r -x "*.dll" -x "obj/*" -x "WINDOWS/*.exe" -x "bin/*.exe" -x "*.zip" -x ".svn"
