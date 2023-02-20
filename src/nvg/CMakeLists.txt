project(honey_engine)

target_sources(honey PUBLIC 
	${CMAKE_CURRENT_LIST_DIR}/color.c
	${CMAKE_CURRENT_LIST_DIR}/composite.c
	${CMAKE_CURRENT_LIST_DIR}/context.c
	${CMAKE_CURRENT_LIST_DIR}/frame.c
	${CMAKE_CURRENT_LIST_DIR}/image.c
	${CMAKE_CURRENT_LIST_DIR}/path.c
	${CMAKE_CURRENT_LIST_DIR}/render.c
	${CMAKE_CURRENT_LIST_DIR}/setup.c
	${CMAKE_CURRENT_LIST_DIR}/state.c
	${CMAKE_CURRENT_LIST_DIR}/transform.c
	${CMAKE_CURRENT_LIST_DIR}/text.c
	${CMAKE_CURRENT_LIST_DIR}/paint.c
	${CMAKE_CURRENT_LIST_DIR}/scissor.c
)
