project(honey_engine)

target_sources(honey PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/glm.c
	${CMAKE_CURRENT_LIST_DIR}/vec3.c
	${CMAKE_CURRENT_LIST_DIR}/mat4.c
	${CMAKE_CURRENT_LIST_DIR}/transform.c
	${CMAKE_CURRENT_LIST_DIR}/camera.c
)
