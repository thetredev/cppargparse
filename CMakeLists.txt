#
# Project setup
#
cmake_minimum_required(VERSION 3.0)
project(cppargparse C CXX)

set(CMAKE_CXX_STANDARD 17)


#
# Include directories
#
include_directories(include)


#
# Third party libraries
#
add_subdirectory(third_party)


#
# Profiling
#
if("${CMAKE_BUILD_TYPE}" STREQUAL "Profiling")
    enable_testing()
    add_subdirectory(test)
endif()
