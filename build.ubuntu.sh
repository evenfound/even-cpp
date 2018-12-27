#!/bin/sh
QT_SELECT=5.12
export QT_SELECT
rm -rf prerequisites/build 2> /dev/null
mkdir prerequisites/build
cd prerequisites/build 
cmake ..
make
cd -
rm -rf even-boffin/build 2> /dev/null
mkdir even-boffin/build
cd even-boffin/build 
cmake .. 
make
cd -
