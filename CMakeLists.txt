
cmake_minimum_required(VERSION 3.18)

project(PigDev VERSION 0.1)

find_package(SDL2 REQUIRED)
find_library(SDL_MIXER_LIBRARY
    NAMES SDL2_mixer
    HINTS
        ENV SDLMIXERDIR
        ENV SDLDIR
    PATH_SUFFIXES lib
)
#find_path(AVCODEC_INCLUDE_DIR libavcodec/avcodec.h)
find_library(AVCODEC_LIBRARY avcodec)
find_library(AVFORMAT_LIBRARY avformat)

# enable_testing()

add_subdirectory(src)
