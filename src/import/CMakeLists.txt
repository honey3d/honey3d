project(honey_engine)

target_sources(honey PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/import.c
)


target_sources(test PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/import.test.c
	${CMAKE_CURRENT_LIST_DIR}/import_mesh.test.c
	${CMAKE_CURRENT_LIST_DIR}/import_node.test.c
	${CMAKE_CURRENT_LIST_DIR}/import_scene.test.c
)
