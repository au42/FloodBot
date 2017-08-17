#!/bin/bash
cd ~/Development/floodbot/script
sh clean.sh
cd ..
cmake . -DCMAKE_TOOLCHAIN_FILE=toolchain-arm.cmake
make
if [ -f "floodbot" ]; then 
echo
echo "Uploading binary to RaspberryPi:"
scp floodbot pi@raspberrypi.local:~/Desktop; 
fi
