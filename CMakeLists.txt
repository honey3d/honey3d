cmake_minimum_required(VERSION 3.2)
project(honey_engine_demo)

find_package(OpenGL REQUIRED)

add_executable(honey_engine_demo demo.c)

add_library(honey_shader "src/shader.c")
add_library(glad "src/glad.c")
add_library(stb_image "src/stb_image.c")

set(LIBRARIES honey_shader glfw GL dl m glad stb_image)
target_link_libraries(honey_engine_demo ${LIBRARIES})


