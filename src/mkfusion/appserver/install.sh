#!/bin/bash

make

cp libmod_mkfusion.so.1.0.0 /usr/lib/apache2/modules/mod_mkfusion.so
#cp install/mkfusion.load /etc/apache2/mods-available
#cp install/mkfusion.conf /etc/apache2/mods-available

/etc/init.d/apache2 restart
