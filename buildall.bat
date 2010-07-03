cd src

qmake

net stop apache2.2

mingw32-make.exe debug

net start apache2.2

cd ..

