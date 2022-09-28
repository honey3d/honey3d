cmake_minimum_required(VERSION 3.2)
project(honey_engine)

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
	${LIB_ROOT}/cglm/include
	${LIB_ROOT}/miniaudio
	${LIB_ROOT}/assimp/include
	# needed for assimp's config.h
	${CMAKE_BINARY_DIR}/libs/assimp/include
)

# disable byte-alignment in cglm
add_definitions(-DCGLM_ALL_UNALIGNED)

# link to third-party included libraries
link_directories(${LIB_ROOT}/assimp/lib)
link_directories(${LIB_ROOT}/honeysuckle)
link_directories(${LIB_ROOT}/glfw-3.3.8/src)

add_subdirectory(${LIB_ROOT}/lua-5.1.5)
add_subdirectory(${LIB_ROOT}/assimp)
add_subdirectory(${LIB_ROOT}/honeysuckle)
add_subdirectory(${LIB_ROOT}/cglm)
add_subdirectory(${LIB_ROOT}/glfw-3.3.8)
add_subdirectory(${LIB_ROOT}/cargs)


set(HONEY_SOURCE ${SRC_ROOT}/main.c)
add_executable(honey ${HONEY_SOURCE})

set(LIBRARIES lua5.1 honeysuckle glfw cargs assimp cairo)
if (WIN32)
	set(LIBRARIES ${LIBRARIES} opengl32)
else()
	set(LIBRARIES ${LIBRARIES} GL dl pthread m)
endif()
target_link_libraries(honey ${LIBRARIES})


# build tests (optional)

string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

add_executable(test EXCLUDE_FROM_ALL)
set_target_properties(test PROPERTIES
	C_STANDARD 99
	CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")
target_link_libraries(test lua5.1 honeysuckle glfw dl)


add_subdirectory(${SRC_ROOT}/audio)
add_subdirectory(${SRC_ROOT}/gl)
add_subdirectory(${SRC_ROOT}/glm)
add_subdirectory(${SRC_ROOT}/image)
add_subdirectory(${SRC_ROOT}/logging)
add_subdirectory(${SRC_ROOT}/options)
add_subdirectory(${SRC_ROOT}/test)
add_subdirectory(${SRC_ROOT}/util)
add_subdirectory(${SRC_ROOT}/import)
