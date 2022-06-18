#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>

/* build a table of all possible window hints */
void create_glfw_window_hints_table(lua_State *L)
{
	/* hint keys */
	hs_create_table(L,
		/* window hints */
		hs_str_int("resizable", GLFW_RESIZABLE),
		hs_str_int("visible", GLFW_VISIBLE),
		hs_str_int("decorated", GLFW_DECORATED),
		hs_str_int("focused", GLFW_FOCUSED),
		hs_str_int("autoIconify", GLFW_AUTO_ICONIFY),
		hs_str_int("floating", GLFW_FLOATING),
		hs_str_int("maximized", GLFW_MAXIMIZED),
		hs_str_int("centerCursor", GLFW_CENTER_CURSOR),
		hs_str_int("transparentFramebuffer", GLFW_TRANSPARENT_FRAMEBUFFER),
		hs_str_int("focusOnShow", GLFW_FOCUS_ON_SHOW),
		hs_str_int("scaleToMonitor", GLFW_SCALE_TO_MONITOR),

		/* framebuffer hints */
		hs_str_int("redBits", GLFW_RED_BITS),
		hs_str_int("greenBits", GLFW_GREEN_BITS),
		hs_str_int("blueBits", GLFW_BLUE_BITS),
		hs_str_int("alphaBits", GLFW_ALPHA_BITS),
		hs_str_int("depthBits", GLFW_DEPTH_BITS),
		hs_str_int("stereoscopic", GLFW_STEREO),
		hs_str_int("samples", GLFW_SAMPLES),
		hs_str_int("srgbCapable", GLFW_SRGB_CAPABLE),
		hs_str_int("doubleBuffer", GLFW_DOUBLEBUFFER),

		/* monitor & context hints */
		hs_str_int("refreshRate", GLFW_REFRESH_RATE),
		hs_str_int("clientApi", GLFW_CLIENT_API),
		hs_str_int("contextCreationApi", GLFW_CONTEXT_CREATION_API),
		hs_str_int("contextVersionMajor", GLFW_CONTEXT_VERSION_MAJOR),
		hs_str_int("contextVersionMinor", GLFW_CONTEXT_VERSION_MINOR),
		hs_str_int("forwardCompatible", GLFW_OPENGL_FORWARD_COMPAT),
		hs_str_int("debugContext", GLFW_OPENGL_DEBUG_CONTEXT),
		hs_str_int("profile", GLFW_OPENGL_PROFILE),
		hs_str_int("contextRobustness", GLFW_CONTEXT_ROBUSTNESS),
		hs_str_int("contextReleaseBehavior", GLFW_CONTEXT_RELEASE_BEHAVIOR),
		hs_str_int("noError", GLFW_CONTEXT_NO_ERROR)
	);

	/* special hint values */
	hs_create_table(L,
		hs_str_int("dontCare", GLFW_DONT_CARE),

		/* client api */
		hs_str_int("glApi", GLFW_OPENGL_API),
		hs_str_int("glesApi", GLFW_OPENGL_ES_API),
		hs_str_int("noApi", GLFW_NO_API),

		/* context api */
		hs_str_int("nativeApi", GLFW_NATIVE_CONTEXT_API),
		hs_str_int("eglApi", GLFW_EGL_CONTEXT_API),
		hs_str_int("osMesaApi", GLFW_OSMESA_CONTEXT_API),

		/* robustness */
		hs_str_int("noRobustness", GLFW_NO_ROBUSTNESS),
		hs_str_int("noResetNotification", GLFW_NO_RESET_NOTIFICATION),
		hs_str_int("loseContextOnReset", GLFW_LOSE_CONTEXT_ON_RESET),

		/* context release */
		hs_str_int("anyBehavior", GLFW_ANY_RELEASE_BEHAVIOR),
		hs_str_int("flush", GLFW_RELEASE_BEHAVIOR_FLUSH),
		hs_str_int("none", GLFW_RELEASE_BEHAVIOR_NONE),

		/* profile */
		hs_str_int("anyProfile", GLFW_OPENGL_ANY_PROFILE),
		hs_str_int("compatabilityProfile", GLFW_OPENGL_COMPAT_PROFILE),
		hs_str_int("coreProfile", GLFW_OPENGL_CORE_PROFILE)
	);
}


int gl_init(lua_State *L)
{
	if (glfwInit() != GLFW_TRUE) {
		hs_throw_error(L, "failed to initialize GLFW");
	}
	return 0;
}


lua_Integer tointeger(lua_State *L, int index)
{
	if (lua_isboolean(L, index)) {
		return lua_toboolean(L, index);
	}
	else if (lua_isnumber(L, index)) {
		return lua_tointeger(L, index);
	}
	else {
		hs_throw_error(L,
			"expected boolean or number; got %s instead",
			lua_typename(L, lua_type(L, index))
		);
	}
}
