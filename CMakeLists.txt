cmake_minimum_required(VERSION 3.8)
project(honey_engine)

if (UNIX)
	set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")
	set(CMAKE_C_FLAGS "-g")
endif()

find_package(OpenGL REQUIRED)

set(SRC_ROOT ${CMAKE_SOURCE_DIR}/src)
set(LIB_ROOT ${CMAKE_SOURCE_DIR}/libs)

set(HONEY_SOURCE ${SRC_ROOT}/main.c)
add_executable(honey ${HONEY_SOURCE})

target_include_directories(
	honey PUBLIC
	${LIB_ROOT}
	${LIB_ROOT}/lua-5.1.5/src 
	${CMAKE_SOURCE_DIR}/src
	${LIB_ROOT}/honeysuckle/src
	${LIB_ROOT}/glfw-3.3.8/include
	${LIB_ROOT}/cglm/include
	${LIB_ROOT}/miniaudio
	${LIB_ROOT}/nanovg/src
)

# link to third-party included libraries
target_link_directories(
	honey PUBLIC
	${LIB_ROOT}/honeysuckle
	${LIB_ROOT}/glfw-3.3.8/src
)

add_subdirectory(${LIB_ROOT}/lua-5.1.5)
add_subdirectory(${LIB_ROOT}/honeysuckle)
add_subdirectory(${LIB_ROOT}/cglm)
add_subdirectory(${LIB_ROOT}/glfw-3.3.8)
add_subdirectory(${LIB_ROOT}/cargs)
add_subdirectory(${LIB_ROOT}/ode-0.16.1)
add_subdirectory(${LIB_ROOT}/nanovg)

target_include_directories(
	honeysuckle PUBLIC
	${LIB_ROOT}/lua-5.1.5/src 
)

set(LIBRARIES lua5.1 honeysuckle glfw cargs ODE nanovg OpenGL::GL)
if (UNIX)
	set(LIBRARIES ${LIBRARIES} dl pthread m)
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
add_subdirectory(${SRC_ROOT}/ode)
add_subdirectory(${SRC_ROOT}/nvg)
