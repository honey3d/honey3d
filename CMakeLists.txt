cmake_minimum_required(VERSION 3.2)
project(honey_engine_demo)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")

find_package(OpenGL REQUIRED)
find_package(Lua51 REQUIRED)

include_directories(${LUA_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)

set(CMAKE_C_FLAGS "-g")

add_library(glad src/glad/glad.c)
add_library(stb_image src/stb_image/stb_image.c)

set(SRC_ROOT ${CMAKE_SOURCE_DIR}/src)
set(SOURCE_FILES
  ${SRC_ROOT}/main.c
  ${SRC_ROOT}/cairo_bindings.c
  ${SRC_ROOT}/glm_bindings.c
  ${SRC_ROOT}/glm_vec3_bindings.c
  ${SRC_ROOT}/glm_vec4_bindings.c
  ${SRC_ROOT}/glm_mat3_bindings.c
  ${SRC_ROOT}/glm_mat4_bindings.c
  ${SRC_ROOT}/honey.c
  ${SRC_ROOT}/input.c
  ${SRC_ROOT}/honey_lua.c
  ${SRC_ROOT}/mesh.c
  ${SRC_ROOT}/shader.c
  ${SRC_ROOT}/texture.c
  ${SRC_ROOT}/window.c)
  
add_executable(honey ${SOURCE_FILES})

set(LIBRARIES ${LUA_LIBRARIES} assimp glad cairo stb_image m)
if (WIN32)
  set(LIBRARIES ${LIBRARIES} glfw3 opengl32)
else()
  set(LIBRARIES ${LIBRARIES} glfw GL dl)
endif()
target_link_libraries(honey ${LIBRARIES})


# build tests (optional)

set(TEST_ROOT ${CMAKE_SOURCE_DIR}/src/test)
set(TEST_SOURCES
  ${TEST_ROOT}/test_main.c
  ${TEST_ROOT}/logging/logging_tests.c

  ${SRC_ROOT}/logging/logging.c
  )
add_executable(test EXCLUDE_FROM_ALL ${TEST_SOURCES})
set_target_properties(test PROPERTIES
  C_STANDARD 99
  CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")
target_link_libraries(test ${LUA_LIBRARIES} honeysuckle)
