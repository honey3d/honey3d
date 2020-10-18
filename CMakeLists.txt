cmake_minimum_required(VERSION 3.2)
project(honey_engine_demo)

#set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")

find_package(OpenGL REQUIRED)
find_package(Lua51 REQUIRED)

include_directories(${LUA_INCLUDE_DIR})

set(CMAKE_C_FLAGS "-g")

add_library(glad src/glad.c)
add_library(stb_image src/stb_image.c)

add_executable(honey src/main.c)

set(LIBRARIES ${LUA_LIBRARIES} assimp glfw GL glad stb_image dl m)
target_link_libraries(honey ${LIBRARIES})


