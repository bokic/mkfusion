#!/bin/sh

DATE=`date +%Y%m%d%H%M%S`

# TODO: please set zip command not to delete empty dirs(ex: bin)

zip mkfusion-0.4.1_$DATE.zip * -r -x "*.dll" -x "Makefile" -x "*.Debug" -x "*.Release" -x "bin/*" -x "deps/*" -x "/docs/*" -x "libs/apache2/*" -x "libs/libssh/*" -x "libs/iis/*" -x "libs/qtservice/*" -x "obj/*" -x "WINDOWS/*.exe" -x "*.zip" -x "*.user"  -x ".svn"
