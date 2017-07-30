#!/bin/bash
cd ~/Development/floodbot/script
sh clean.sh
cd ..
cmake . -DCMAKE_TOOLCHAIN_FILE=toolchain-arm.cmake
make
