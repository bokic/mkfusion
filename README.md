mkfusion - Your native CFML implementation
====

MKFusion is a free opensource CFML application server.
Utilizing C++ to convert cfm/cfc files to dll/so dynamic libraries, MKFusion is able to achieve incredible performance while keeping memory usage to minimum.

Precompiled packages:
Windows - http://sourceforge.net/projects/mkfusion/files/
Ubuntu 15.04, 14.10 are supported from repository(see below for more details).
Older Ubuntu versions need to compile from sources.

install:
* sudo add-apt-repository http://ppa.launchpad.net/bbarbulovski-gmail/mkfusion-daily/ubuntu
* sudo apt-get update
* sudo apt-get install mkfusion libapache2-mod-mkfusion

uninstall:
* sudo apt-get purge mkfusion libapache2-mod-mkfusion
* sudo add-apt-repository -r http://ppa.launchpad.net/bbarbulovski-gmail/mkfusion-daily/ubuntu
* sudo apt-get update
