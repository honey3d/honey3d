project(honey_engine)

set (GL ${CMAKE_CURRENT_LIST_DIR})

target_sources(honey PUBLIC
	${GL}/data.c
	${GL}/drawing.c
	${GL}/shader.c
	${GL}/window.c
	${GL}/texture.c
	${GL}/gl.c
)


target_sources(test PUBLIC
	${GL}/gl.test.c
	${GL}/window.test.c
)


add_subdirectory(glad)
