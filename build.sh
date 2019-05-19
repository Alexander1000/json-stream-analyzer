#!/bin/bash

# set -xe

rm -rf CMakeFiles
rm -f CMakeCache.txt
rm -f Makefile
rm -f libjson-stream-analyzer*

cmake .
make
make install

cd cli

echo "Compile cli application"

rm -rf CMakeFiles
rm -f CMakeCache.txt

cmake .
make
