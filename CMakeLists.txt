cmake_minimum_required(VERSION 3.12)

project(AOC_2019 CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_subdirectory(deps)
add_subdirectory(lib)
add_subdirectory(app)