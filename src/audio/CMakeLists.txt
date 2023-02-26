project(honey_engine)

target_sources(honey PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/impl.c
	${CMAKE_CURRENT_LIST_DIR}/setup.c
	${CMAKE_CURRENT_LIST_DIR}/engine.c
	${CMAKE_CURRENT_LIST_DIR}/sound.c
)
