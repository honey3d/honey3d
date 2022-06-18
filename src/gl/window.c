#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>


void create_glfw_window_hints_table(lua_State *L)
{
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
}

int gl_init(lua_State *L)
{
	if (glfwInit() != GLFW_TRUE) {
		hs_throw_error(L, "failed to initialize GLFW");
	}
	return 0;
}
