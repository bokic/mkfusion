#!/bin/sh

chmod 0755 *.sh

cd src
qmake
make qmake_all
cd mkfusion
qmake
make qmake_all
cd ../tests
qmake
make qmake_all
cd ..
make release
cd ..

sudo su&

mkdir install/ubuntu/mkfusion
mkdir install/ubuntu/mkfusion/DEBIAN
mkdir install/ubuntu/mkfusion/opt
mkdir install/ubuntu/mkfusion/opt/mkfusion
mkdir install/ubuntu/mkfusion/opt/mkfusion/bin
mkdir install/ubuntu/mkfusion/opt/mkfusion/include
mkdir install/ubuntu/mkfusion/opt/mkfusion/logs
mkdir install/ubuntu/mkfusion/opt/mkfusion/templates
mkdir install/ubuntu/mkfusion/etc
mkdir install/ubuntu/mkfusion/etc/apache2
mkdir install/ubuntu/mkfusion/etc/apache2/mods-available
mkdir install/ubuntu/mkfusion/etc/apache2/mods-enabled
cp install/ubuntu/mkfusion_control install/ubuntu/mkfusion/DEBIAN/control
cp install/ubuntu/mkfusion_postinst install/ubuntu/mkfusion/DEBIAN/postinst
chmod 0755 install/ubuntu/mkfusion/DEBIAN/postinst
cp install/ubuntu/mkfusion_prerm install/ubuntu/mkfusion/DEBIAN/prerm
chmod 0755 install/ubuntu/mkfusion/DEBIAN/prerm
cp bin/mkfusion install/ubuntu/mkfusion/opt/mkfusion/bin/mkfusion
cp bin/libmod_mkfusion.so.1.0.0 install/ubuntu/mkfusion/opt/mkfusion/bin/mod_mkfusion.so
chmod 0644 install/ubuntu/mkfusion/opt/mkfusion/bin/mod_mkfusion.so
cp src/mkfusion/appserver/cffunctions.h install/ubuntu/mkfusion/opt/mkfusion/include/cffunctions.h
cp src/mkfusion/appserver/common.h install/ubuntu/mkfusion/opt/mkfusion/include/common.h
cp src/mkfusion/appserver/qcfrunningtemplate.h install/ubuntu/mkfusion/opt/mkfusion/include/qcfrunningtemplate.h
cp src/mkfusion/appserver/qcftemplate.h install/ubuntu/mkfusion/opt/mkfusion/include/qcftemplate.h
cp src/mkfusion/appserver/qmkfusionexception.h install/ubuntu/mkfusion/opt/mkfusion/include/qmkfusionexception.h
cp src/mkfusion/appserver/qwddx.h install/ubuntu/mkfusion/opt/mkfusion/include/qwddx.h
cp install/ubuntu/mkfusion_mkfusion.conf install/ubuntu/mkfusion/etc/apache2/mods-available/mkfusion.conf
ln -s ../mods-available/mkfusion.conf install/ubuntu/mkfusion/etc/apache2/mods-enabled/mkfusion.conf
chmod 0644 install/ubuntu/mkfusion/etc/apache2/mods-enabled/mkfusion.conf
cp install/ubuntu/mkfusion_mkfusion.load install/ubuntu/mkfusion/etc/apache2/mods-available/mkfusion.load
ln -s ../mods-available/mkfusion.load install/ubuntu/mkfusion/etc/apache2/mods-enabled/mkfusion.load
dpkg -b install/ubuntu/mkfusion mkfusion_0.4.1-0ubuntu0_i386.deb
rm -rf install/ubuntu/mkfusion

mkdir install/ubuntu/cfeditor
mkdir install/ubuntu/cfeditor/DEBIAN
mkdir install/ubuntu/cfeditor/usr
mkdir install/ubuntu/cfeditor/usr/bin
cp install/ubuntu/cfeditor_control install/ubuntu/cfeditor/DEBIAN/control
cp install/ubuntu/cfeditor_postinst install/ubuntu/cfeditor/DEBIAN/postinst
chmod 0755 install/ubuntu/cfeditor/DEBIAN/postinst
cp bin/cfeditor install/ubuntu/cfeditor/usr/bin/cfeditor
dpkg -b install/ubuntu/cfeditor cfeditor_0.4.1-0ubuntu0_i386.deb
rm -rf install/ubuntu/cfeditor

exit
