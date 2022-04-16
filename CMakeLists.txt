cmake_minimum_required(VERSION 3.2)
project(honey_engine_demo)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")
set(CMAKE_C_FLAGS "-g")

find_package(OpenGL REQUIRED)
find_package(Lua51 REQUIRED)

include_directories(${LUA_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)
# link to third-party included libraries
link_directories(${SRC_ROOT}/mesh/assimp-master/lib)

set(SRC_ROOT ${CMAKE_SOURCE_DIR}/src)

add_library(glad ${SRC_ROOT}/gl/glad/glad.c)
# add_library(stb_image src/stb_image/stb_image.c)
add_subdirectory(${SRC_ROOT}/mesh/assimp-master)


set(HONEY_LIB_FILES
  ${SRC_ROOT}/logging/logging.c
  ${SRC_ROOT}/gl/honey_window.c
  ${SRC_ROOT}/options/honey_options.c
  )

set(SOURCE_FILES
  ${SRC_ROOT}/main.c
  ${HONEY_LIB_FILES}
  )
  
add_executable(honey ${SOURCE_FILES})

set(LIBRARIES ${LUA_LIBRARIES} honeysuckle assimp glad cairo m)
if (WIN32)
  set(LIBRARIES ${LIBRARIES} glfw3 opengl32)
else()
  set(LIBRARIES ${LIBRARIES} glfw GL dl)
endif()
target_link_libraries(honey ${LIBRARIES})


# build tests (optional)

set(TEST_SOURCES
  ${SRC_ROOT}/test/test_main.c
  ${HONEY_LIB_FILES}

  ${SRC_ROOT}/test/mock_queue.c
  ${SRC_ROOT}/test/mock_queue.test.c

  ${SRC_ROOT}/logging/logging.test.c
  ${SRC_ROOT}/gl/honey_gl.test.c
  )

add_executable(test EXCLUDE_FROM_ALL ${TEST_SOURCES})
set_target_properties(test PROPERTIES
  C_STANDARD 99
  CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")
target_link_libraries(test ${LUA_LIBRARIES} honeysuckle)
