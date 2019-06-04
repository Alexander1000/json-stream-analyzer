#!/bin/bash

rm -rf CMakeFiles
rm -f cmake_install.cmake
rm -f json-analyzer-tests
rm -f Makefile

cmake .

make

./json-analyzer-tests
