#ifndef HONEY_GLM_H
#define HONEY_GLM_H

#include <lua.h>


extern const char *glm_mat2_tname;
extern const char *glm_mat3_tname;
extern const char *glm_mat4_tname;
extern const char *glm_vec2_tname;
extern const char *glm_vec3_tname;
extern const char *glm_vec4_tname;


#define GLM_FUNCTIONS \
	/* 3d affine transforms */ \
	X("decompose", glm_decompose_bind) \
	X("decompose_rs", glm_decompose_rs_bind) \
	X("decompose_scalev", glm_decompose_scalev_bind) \
	X("rotate", glm_rotate_bind) \
	X("rotate_at", glm_rotate_at_bind) \
	X("rotate_atm", glm_rotate_atm_bind) \
	X("rotate_make", glm_rotate_make_bind) \
	X("rotate_x", glm_rotate_x_bind) \
	X("rotate_y", glm_rotate_y_bind) \
	X("rotate_z", glm_rotate_z_bind) \
	X("scale", glm_scale_bind) \
	X("scale_make", glm_scale_make_bind) \
	X("scale_to", glm_scale_to_bind) \
	X("scale_uni", glm_scale_uni_bind) \
	X("translate", glm_translate_bind) \
	X("translate_make", glm_translate_make_bind) \
	X("translate_to", glm_translate_to_bind) \
	X("translate_x", glm_translate_x_bind) \
	X("translate_y", glm_translate_y_bind) \
	X("translate_z", glm_translate_z_bind) \
	X("uniscaled", glm_uniscaled_bind) \
\
	/* vec3 */ \
	X("vec3_create", glm_vec3_create) \
	X("vec3_set", glm_vec3_set) \
	X("vec3_get", glm_vec3_get) \
	X("vec3", glm_vec3_bind) \
	X("vec3_copy", glm_vec3_copy_bind) \
	X("vec3_zero", glm_vec3_zero_bind) \
	X("vec3_one", glm_vec3_one_bind) \
	X("vec3_dot", glm_vec3_dot_bind) \
	X("vec3_norm2", glm_vec3_norm2_bind) \
	X("vec3_norm", glm_vec3_norm_bind) \
	X("vec3_add", glm_vec3_add_bind) \
	X("vec3_adds", glm_vec3_adds_bind) \
	X("vec3_sub", glm_vec3_sub_bind) \
	X("vec3_subs", glm_vec3_subs_bind) \
	X("vec3_mul", glm_vec3_mul_bind) \
	X("vec3_scale", glm_vec3_scale_bind) \
	X("vec3_scale_as", glm_vec3_scale_as_bind) \
	X("vec3_div", glm_vec3_div_bind) \
	X("vec3_divs", glm_vec3_divs_bind) \
	X("vec3_addadd", glm_vec3_addadd_bind) \
	X("vec3_subadd", glm_vec3_subadd_bind) \
	X("vec3_muladd", glm_vec3_muladd_bind) \
	X("vec3_muladds", glm_vec3_muladds_bind) \
	X("vec3_maxadd", glm_vec3_maxadd_bind) \
	X("vec3_minadd", glm_vec3_minadd_bind) \
	X("vec3_flipsign", glm_vec3_flipsign_bind) \
	X("vec3_flipsign_to", glm_vec3_flipsign_to_bind) \
	X("vec3_inv", glm_vec3_inv_bind) \
	X("vec3_inv_to", glm_vec3_inv_to_bind) \
	X("vec3_negate", glm_vec3_negate_bind) \
	X("vec3_negate_to", glm_vec3_negate_to_bind) \
	X("vec3_normalize", glm_vec3_normalize_bind) \
	X("vec3_normalize_to", glm_vec3_normalize_to_bind) \
	X("vec3_cross", glm_vec3_cross_bind) \
	X("vec3_crossn", glm_vec3_crossn_bind) \
	X("vec3_distance2", glm_vec3_distance2_bind) \
	X("vec3_distance", glm_vec3_distance_bind) \
	X("vec3_angle", glm_vec3_angle_bind) \
	X("vec3_rotate", glm_vec3_rotate_bind) \
	X("vec3_rotate_m4", glm_vec3_rotate_m4_bind) \
	X("vec3_rotate_m3", glm_vec3_rotate_m3_bind) \
	X("vec3_proj", glm_vec3_proj_bind) \
	X("vec3_center", glm_vec3_center_bind) \
	X("vec3_maxv", glm_vec3_maxv_bind) \
	X("vec3_minv", glm_vec3_minv_bind) \
	X("vec3_ortho", glm_vec3_ortho_bind) \
	X("vec3_clamp", glm_vec3_clamp_bind) \
	X("vec3_lerp", glm_vec3_lerp_bind) \


#define X(name, func) int func(lua_State *L);
GLM_FUNCTIONS
#undef X

#endif
