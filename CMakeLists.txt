cmake_minimum_required(VERSION 3.2)
project(honey_engine_demo)

#set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")

find_package(OpenGL REQUIRED)

add_executable(honey_engine_demo demo.c)

set(CMAKE_C_FLAGS "-g")

add_library(honey src/honey.c src/camera.c src/error.c src/input.c src/mesh.c src/model.c src/primitives.c src/shader.c src/texture.c)
add_library(glad src/glad.c)
add_library(stb_image src/stb_image.c)

set(LIBRARIES honey assimp glfw GL glad stb_image dl m)
target_link_libraries(honey_engine_demo ${LIBRARIES})


