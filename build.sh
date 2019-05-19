#!/bin/bash

rm -rf CMakeFiles
rm -f CMakeCache.txt

cmake .
make
make install

cd cli

rm -rf CMakeFiles
rm -f CMakeCache.txt

cmake .
make
