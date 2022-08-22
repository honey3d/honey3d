project(honey_engine)

set (GL ${CMAKE_CURRENT_LIST_DIR})

target_sources(honey PUBLIC
	${GL}/data.c
	${GL}/drawing.c
	${GL}/shader.c
	${GL}/window.c
	${GL}/gl.c
	${GL}/glad/glad.c
)
