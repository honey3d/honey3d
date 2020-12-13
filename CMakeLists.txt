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
  src/cairo_bindings.c
  src/glm_bindings.c
  src/glm_vec3_bindings.c
  src/glm_vec4_bindings.c
  src/glm_mat3_bindings.c
  src/glm_mat4_bindings.c
  src/honey.c
  src/input.c
  src/honey_lua.c
  src/mesh.c
  src/shader.c
  src/texture.c
  src/window.c)
  
add_executable(honey ${SOURCE_FILES})

set(LIBRARIES ${LUA_LIBRARIES} assimp glad cairo stb_image m)
if (WIN32)
  set(LIBRARIES ${LIBRARIES} glfw3 opengl32)
else()
  set(LIBRARIES ${LIBRARIES} glfw GL dl)
endif()
target_link_libraries(honey ${LIBRARIES})


