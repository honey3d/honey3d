project(honey_engine)

target_sources(honey PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/glm.c
	${CMAKE_CURRENT_LIST_DIR}/mat4.c
	${CMAKE_CURRENT_LIST_DIR}/transform.c
)
