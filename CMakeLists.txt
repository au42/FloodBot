cmake_minimum_required (VERSION 3.0)

project (floodbot)

set (WPI_PATH /home/alex/Development/wiringPi/wiringPi)

include_directories (include)
include_directories (${WPI_PATH})

find_library(WPI_LIB wiringPi HINTS ${WPI_PATH} NO_CMAKE_FIND_ROOT_PATH)
#if(NOT WPI_LIB)
#  message(FATAL_ERROR "wiringPi library not found")
#endif()


FILE(GLOB SRC_FILES src/*.c)
add_executable(floodbot ${SRC_FILES})


target_link_libraries(floodbot ${WPI_LIB})


