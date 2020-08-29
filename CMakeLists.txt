
cmake_minimum_required(VERSION 3.18)

project(PigDev VERSION 0.7.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(PigConfig.h.in PigConfig.h)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ffmpeg)

add_subdirectory(src)
add_subdirectory(examples)
