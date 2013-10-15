#!/bin/sh

rm -f ../mkfusion_0.5.0*
rm -f ../mkfusion-generator_0.5.0*
rm -f ../cfeditor_0.5.0*
rm -f ../libapache2-mod-mkfusion_0.5.0*

rm -f bin/mkfusion
rm -f bin/libmod_mkfusion*

dh_make -p mkfusion_0.5.0 -m -y -d -c lgpl3 --createorig || debuild

rm -f debian/files

rm -f debian/mkfusion.debhelper.log
rm -f debian/mkfusion-generator.debhelper.log
rm -f debian/cfeditor.debhelper.log
rm -f debian/libapache2-mod-mkfusion.debhelper.log

rm -f debian/mkfusion.substvars
rm -f debian/mkfusion-generator.substvars
rm -f debian/cfeditor.substvars
rm -f debian/libapache2-mod-mkfusion.substvars

rm -fr debian/mkfusion
rm -fr debian/mkfusion-generator
rm -fr debian/cfeditor
rm -fr debian/libapache2-mod-mkfusion
