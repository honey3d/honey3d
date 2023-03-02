project(honey-engine)

target_sources(honey PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/src/glad.c
)

target_include_directories(honey PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/include
)
