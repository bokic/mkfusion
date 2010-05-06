#!/bin/sh

cd src
qmake
make qmake_all
make release
cd ..

dpkg -b install/ubuntu/mkfusion/ mkfusion_0.4.1-0ubuntu0_i386.deb
dpkg -b install/ubuntu/cfeditor/ mkfusion_0.4.1-0ubuntu0_i386.deb
