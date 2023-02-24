project(honey_engine)

target_sources(honey PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/setup.c
	${CMAKE_CURRENT_LIST_DIR}/world.c
	${CMAKE_CURRENT_LIST_DIR}/body.c
	${CMAKE_CURRENT_LIST_DIR}/joint.c
	${CMAKE_CURRENT_LIST_DIR}/geom.c
)


target_sources(test PUBLIC
)
