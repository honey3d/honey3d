project(honey_engine)

target_sources(test PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/honey-test.c
	${CMAKE_CURRENT_LIST_DIR}/lily-test.c
)
