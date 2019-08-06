cmake_minimum_required(VERSION 3.13)
project(cppargparse C CXX)

set(CMAKE_CXX_STANDARD 17)


include_directories(include)
add_subdirectory(include)

add_subdirectory(test)
