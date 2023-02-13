# added by me (sanine) for build compatibility
# this is not a part of the original nanovg code

cmake_minimum_required(VERSION 3.2)
project(nanovg)

add_library(nanovg STATIC src/nanovg.c)
target_include_directories(nanovg PUBLIC src)
