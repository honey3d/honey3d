#ifndef HONEY_COMMON_H
#define HONEY_COMMON_H

#include <lua.h>

#define HONEY_MODULES \
	X(audio) \
	X(gl) \
	X(glm) \
	X(image) \
	X(import) \
	X(logging) \
	X(ode) \
	X(util) \
	X(window) \
	X(nvg) \


#define X(module) \
	void setup_ ## module (lua_State *L, int honey_index);
HONEY_MODULES
#undef X


#endif
