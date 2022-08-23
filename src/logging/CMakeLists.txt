project(honey_engine)

target_sources(honey PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/logging.c
)


target_sources(test PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/logging.test.c
)
