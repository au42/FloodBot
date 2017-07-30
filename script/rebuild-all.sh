#!/bin/bash
cd ~/Development/wiringPi/wiringPi
sh clean.sh
cmake . -DCMAKE_TOOLCHAIN_FILE=toolchain-arm.cmake
make
cd ~/Development/floodbot/script
sh clean.sh
cd ..
cmake . -DCMAKE_TOOLCHAIN_FILE=toolchain-arm.cmake
make