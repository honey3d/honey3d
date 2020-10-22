cmake_minimum_required(VERSION 3.2)
project(honey_engine_demo)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")

find_package(OpenGL REQUIRED)
find_package(Lua51 REQUIRED)

include_directories(${LUA_INCLUDE_DIR})

set(CMAKE_C_FLAGS "-g")

add_library(glad src/glad/glad.c)
add_library(stb_image src/stb_image/stb_image.c)

set(SOURCE_FILES
  src/main.c
  src/camera/camera.c
  src/error/error.c
  src/honey.c
  src/input/input.c
  src/honey_lua.c
  src/light/light.c
  src/mesh/mesh.c
  src/model/model.c
  src/primitives/primitives.c
  src/shader/shader.c
  src/texture/texture.c)
  
add_executable(honey ${SOURCE_FILES})

set(LIBRARIES ${LUA_LIBRARIES} assimp glfw GL glad stb_image dl m)
target_link_libraries(honey ${LIBRARIES})


