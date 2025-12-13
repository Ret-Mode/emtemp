cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 11)
project(initproj)

add_executable(template)
target_sources(template PRIVATE main.cpp)
target_compile_options(template PRIVATE --use-port=sdl2)
#target_compile_options(template PRIVATE -save-temps)

