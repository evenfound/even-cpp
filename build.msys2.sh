#!sh
rm -rf prerequisites/build 2> /dev/null
mkdir prerequisites/build
cd prerequisites/build 
cmake -G "MSYS Makefiles" .. 
make
cd -
rm -rf even-boffin/build 2> /dev/null
mkdir even-boffin/build
cd even-boffin/build 
cmake -G "MSYS Makefiles" .. 
make
cd -