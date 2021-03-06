#!/bin/bash

# set -xe

echo "#--------------------------#"
echo "#      BUILD LIBRARY       #"
echo "#--------------------------#"

echo "+++++++++++++++++"
echo "++ CLEAR CACHE ++"
echo "+++++++++++++++++"

rm -rf CMakeFiles
rm -f CMakeCache.txt
rm -f Makefile
rm -f libjson-stream-analyzer*

echo "+++++++++++++++++++"
echo "++     CMAKE     ++"
echo "+++++++++++++++++++"

cmake .

echo "++++++++++++++++++"
echo "++     MAKE     ++"
echo "++++++++++++++++++"

make

echo "+++++++++++++++++++++"
echo "++     INSTALL     ++"
echo "+++++++++++++++++++++"

make install

echo "+++++++++++++++++"
echo "++ BUILD TESTS ++"
echo "+++++++++++++++++"

cd tests
rm -rf CMakeFiles
rm -f cmake_install.cmake
rm -f json-analyzer-tests
rm -f Makefile

cmake .

make

./json-analyzer-tests
