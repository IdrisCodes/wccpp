cmake_minimum_required(VERSION 3.22)
project(wccpp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

add_subdirectory(src)

include(CTest)
enable_testing()
add_subdirectory(tests)