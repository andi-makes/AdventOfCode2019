cmake_minimum_required(VERSION 3.10)

set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)

include_directories(lib/)

add_executable(d1.x d1/main.cpp)
add_executable(d2.x d2/main.cpp)
add_executable(d3.x d3/main.cpp)
add_executable(d4.x d4/main.cpp)
add_executable(d5.x d5/main.cpp)
add_executable(d6.x d6/main.cpp)
add_executable(test.x test/main.cpp)