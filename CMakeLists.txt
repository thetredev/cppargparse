#
# Project setup
#
cmake_minimum_required(VERSION 3.1)
project(cppargparse C CXX)

set(ignoreMe ${QT_QMAKE_EXECUTABLE})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


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
if("${CMAKE_BUILD_TYPE}" MATCHES "^(debug|Debug|DEBUG|profiling|Profiling|PROFILING)$")
    enable_testing()
    add_subdirectory(test)
endif()
