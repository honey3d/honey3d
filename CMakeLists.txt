cmake_minimum_required(VERSION 3.2)
project(honey_engine_demo)

if (UNIX)
	set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")
	set(CMAKE_C_FLAGS "-g")
endif()

find_package(OpenGL REQUIRED)

set(SRC_ROOT ${CMAKE_SOURCE_DIR}/src)
set(LIB_ROOT ${CMAKE_SOURCE_DIR}/libs)

include_directories(
	${LIB_ROOT}/lua-5.1.5/src 
	${CMAKE_SOURCE_DIR}/src
	${LIB_ROOT}/honeysuckle/src
	${LIB_ROOT}/glfw-3.3.8/include
)

# link to third-party included libraries
link_directories(${LIB_ROOT}/assimp/lib)
link_directories(${LIB_ROOT}/honeysuckle)
link_directories(${LIB_ROOT}/glfw-3.3.8/src)

# add_library(glad ${SRC_ROOT}/gl/glad/glad.c)
# add_library(stb_image src/stb_image/stb_image.c)
add_subdirectory(${LIB_ROOT}/lua-5.1.5)
add_subdirectory(${LIB_ROOT}/assimp)
add_subdirectory(${LIB_ROOT}/honeysuckle)
add_subdirectory(${LIB_ROOT}/cglm)
add_subdirectory(${LIB_ROOT}/glfw-3.3.8)


set(HONEY_LIB_FILES
	${SRC_ROOT}/logging/logging.c
	${SRC_ROOT}/gl/glad/glad.c
	${SRC_ROOT}/gl/gl.c
	${SRC_ROOT}/gl/shader.c
	${SRC_ROOT}/gl/drawing.c
	${SRC_ROOT}/gl/data.c
	${SRC_ROOT}/gl/window.c
)

set(SOURCE_FILES
	${SRC_ROOT}/main.c
	${HONEY_LIB_FILES}
	)
	
add_executable(honey ${SOURCE_FILES})

set(LIBRARIES lua5.1 honeysuckle assimp glfw)
if (WIN32)
	set(LIBRARIES ${LIBRARIES} opengl32)
else()
	set(LIBRARIES ${LIBRARIES} GL dl m)
endif()
target_link_libraries(honey ${LIBRARIES})


# build tests (optional)

string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

set(TEST_SOURCES
	${SRC_ROOT}/test/lily-test.c
	${SRC_ROOT}/test/honey-test.c

	${SRC_ROOT}/logging/logging.test.c
	${SRC_ROOT}/gl/glad/glad.c
	${SRC_ROOT}/gl/gl.test.c
	${SRC_ROOT}/gl/window.test.c
)

add_executable(test EXCLUDE_FROM_ALL ${TEST_SOURCES})
set_target_properties(test PROPERTIES
	C_STANDARD 99
	CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")
target_link_libraries(test lua5.1 honeysuckle glfw dl)
