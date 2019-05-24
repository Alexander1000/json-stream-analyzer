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

cd cli

echo "#------------------------------#"
echo "#      BUILD APPLICATION       #"
echo "#------------------------------#"

echo "+++++++++++++++++"
echo "++ CLEAR CACHE ++"
echo "+++++++++++++++++"

rm -rf CMakeFiles
rm -f CMakeCache.txt

echo "+++++++++++++++++++"
echo "++     CMAKE     ++"
echo "+++++++++++++++++++"

cmake .

echo "++++++++++++++++++"
echo "++     MAKE     ++"
echo "++++++++++++++++++"

make
