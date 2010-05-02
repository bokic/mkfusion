#!/bin/sh

cd src
qmake
make qmake_all
make release
cd ..

