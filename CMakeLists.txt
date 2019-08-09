cmake_minimum_required(VERSION 3.13)
project(cppargparse C CXX)

set(CMAKE_CXX_STANDARD 17)


include_directories(include)

add_subdirectory(third_party)


if("${CMAKE_BUILD_TYPE}" STREQUAL "Profiling")
    enable_testing()
    add_subdirectory(test)
endif()
