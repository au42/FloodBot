cmake_minimum_required (VERSION 3.0)

project (floodbot)

set (WPI_PATH /home/alex/Development/wiringPi/wiringPi)
set (LIBCONF_PATH /home/alex/Development/libconfig/lib)

include_directories (include)
include_directories (${WPI_PATH})
include_directories (${LIBCONF_PATH})

find_library(WPI_LIB wiringPi HINTS ${WPI_PATH} NO_CMAKE_FIND_ROOT_PATH)
if(NOT WPI_LIB)
  message(FATAL_ERROR "wiringPi library not found")
endif()

find_library(LIBCONF_PATH libconfig HINTS ${LIBCONF_PATH} NO_CMAKE_FIND_ROOT_PATH)
if(NOT LIBCONF_PATH)
  message(FATAL_ERROR "libconfig library not found")
endif()

FILE(GLOB SRC_FILES src/*.c)
add_executable(floodbot ${SRC_FILES})


target_link_libraries(floodbot ${WPI_LIB})


