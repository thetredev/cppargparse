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
# Install target
#
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX})


#
# Third party libraries
#
add_subdirectory(third_party)


#
# Samples
#
add_subdirectory(samples)


#
# Profiling
#
if("${CMAKE_BUILD_TYPE}" STREQUAL "Profiling")
    enable_testing()
    add_subdirectory(test)
endif()
