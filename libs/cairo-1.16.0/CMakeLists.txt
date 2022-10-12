project(cairo)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Freetype)
find_package(Threads)
find_package(Fontconfig)


include(Configure_config.cmake)
include(Configure_features.cmake)
include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_SOURCE_DIR}/libs/pixman-0.40.0/pixman 
	${CMAKE_SOURCE_DIR}/libs/assimp/contrib/zlib
	${CMAKE_CURRENT_LIST_DIR}/libpng
)
link_directories(
	${CMAKE_SOURCE_DIR}/libs/pixman-0.40.0/pixman 
	${CMAKE_SOURCE_DIR}/libs/assimp/contrib/zlib
	${CMAKE_BINARY_DIR}/libs/assimp/contrib/zlib
	${CMAKE_CURRENT_LIST_DIR}/libpng
	${CMAKE_CURRENT_BINARY_DIR}/libpng
)

add_subdirectory(libpng)

if(CAIRO_HAS_PTHREAD)
	list(APPEND CAIRO_LIBS -lpthread)
endif()

if (WIN32)
    set(CAIRO_LIBS gdi32 msimg32 user32 winmm)
endif()



list(APPEND CAIRO_LIBS  pixman-1_static png_static zlibstatic)

if(FONTCONFIG_FOUND)
    list(APPEND CAIRO_LIBS ${FONTCONFIG_LIBRARY})
endif()

if(FREETYPE_FOUND)
    find_package(BZip2)
    include_directories(${FREETYPE_INCLUDE_DIRS})
    include_directories(${BZIP2_INCLUDE_DIR})
    list(APPEND CAIRO_LIBS ${FREETYPE_LIBRARIES} ${BZIP2_LIBRARIES})
endif()

include_directories(src)
add_subdirectory(src)
