cmake_minimum_required (VERSION 3.0)

# Have CMake find our pthreads library within our toolchain (required for this library)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)


project (floodbot)

set (WPI_PATH /home/alex/Development/wiringPi/wiringPi)
set (LIBCONF_PATH /home/alex/Development/libconfig/lib)
set (LIB_PATH /home/alex/Development/raspberrypi-tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot/lib)

include_directories (include)
include_directories (${WPI_PATH})
include_directories (${LIBCONF_PATH})

find_library(WPI_LIB wiringPi HINTS ${WPI_PATH} NO_CMAKE_FIND_ROOT_PATH)
if(NOT WPI_LIB)
  message(FATAL_ERROR "wiringPi library not found")
endif()

find_library(LIBCONF_LIB NAMES libconfig.so PATHS ${LIB_PATH})
if(NOT LIBCONF_LIB)
  message(FATAL_ERROR "libconfig library not found")
endif()

FILE(GLOB SRC_FILES src/*.c)
add_executable(floodbot ${SRC_FILES})
find_package(Threads REQUIRED)

target_link_libraries(floodbot ${WPI_LIB} ${LIBCONF_LIB} ${CMAKE_THREAD_LIBS_INIT})


