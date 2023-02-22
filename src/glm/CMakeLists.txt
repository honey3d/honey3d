project(honey_engine)

target_sources(honey PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/setup.c
	${CMAKE_CURRENT_LIST_DIR}/vec3.c
	${CMAKE_CURRENT_LIST_DIR}/affine3d.c
)
