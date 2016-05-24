cmake_minimum_required(VERSION 3.5)
project(arm11_19)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

include_directories("src")
add_executable(arm11_19 src/emulate.c ${SOURCE_FILES})