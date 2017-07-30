#!/bin/bash
# This script moves to the base project directory and removes all the cmake build artifacts
cd ~/Development/floodbot
rm cmake_install.cmake
rm -rf CMakeFiles
rm Makefile
rm CMakeCache.txt
rm floodbot
