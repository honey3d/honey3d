#ifndef HONEY_GLM_H
#define HONEY_GLM_H

#include <lua.h>


extern const char *glm_mat2_tname;
extern const char *glm_mat3_tname;
extern const char *glm_mat4_tname;
extern const char *glm_vec2_tname;
extern const char *glm_vec3_tname;
extern const char *glm_vec4_tname;
extern const char *glm_versor_tname;


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
	/* 2d affine transforms */ \
	X("translate2d", glm_translate2d_bind) \
	X("translate2d_to", glm_translate2d_to_bind) \
	X("translate2d_x", glm_translate2d_x_bind) \
	X("translate2d_y", glm_translate2d_y_bind) \
	X("translate2d_make", glm_translate2d_make_bind) \
	X("scale2d_to", glm_scale2d_to_bind) \
	X("scale2d_make", glm_scale2d_make_bind) \
	X("scale2d", glm_scale2d_bind) \
	X("scale2d_uni", glm_scale2d_uni_bind) \
	X("rotate2d_make", glm_rotate2d_make_bind) \
	X("rotate2d", glm_rotate2d_bind) \
	X("rotate2d_to", glm_rotate2d_to_bind) \
\
	/* camera */ \
	X("frustum", glm_frustum_bind) \
	X("ortho", glm_ortho_bind) \
	X("ortho_aabb", glm_ortho_aabb_bind) \
	X("ortho_aabb_p", glm_ortho_aabb_p_bind) \
	X("ortho_aabb_pz", glm_ortho_aabb_pz_bind) \
	X("ortho_default", glm_ortho_default_bind) \
	X("ortho_default_s", glm_ortho_default_s_bind) \
	X("perspective", glm_perspective_bind) \
	X("persp_move_far", glm_persp_move_far_bind) \
	X("perspective_default", glm_perspective_default_bind) \
	X("perspective_resize", glm_perspective_resize_bind) \
	X("lookat", glm_lookat_bind) \
	X("look", glm_look_bind) \
	X("look_anyup", glm_look_anyup_bind) \
	X("persp_decomp", glm_persp_decomp_bind) \
	X("persp_decomp_x", glm_persp_decomp_x_bind) \
	X("persp_decomp_y", glm_persp_decomp_y_bind) \
	X("persp_decomp_z", glm_persp_decomp_z_bind) \
	X("persp_decomp_far", glm_persp_decomp_far_bind) \
	X("persp_decomp_near", glm_persp_decomp_near_bind) \
	X("persp_fovy", glm_persp_fovy_bind) \
	X("persp_aspect", glm_persp_aspect_bind) \
	X("persp_sizes", glm_persp_sizes_bind) \
\
	/* quaternions */ \
	X("quat_create", glm_quat_create) \
	X("quat_identity", glm_quat_identity_bind) \
	X("quat_init", glm_quat_init_bind) \
	X("quat", glm_quat_bind) \
	X("quatv", glm_quatv_bind) \
	X("quat_copy", glm_quat_copy_bind) \
	X("quat_from_vecs", glm_quat_from_vecs_bind) \
	X("quat_norm", glm_quat_norm_bind) \
	X("quat_normalize_to", glm_quat_normalize_to_bind) \
	X("quat_normalize", glm_quat_normalize_bind) \
	X("quat_dot", glm_quat_dot_bind) \
	X("quat_conjugate", glm_quat_conjugate_bind) \
	X("quat_inv", glm_quat_inv_bind) \
	X("quat_add", glm_quat_add_bind) \
	X("quat_sub", glm_quat_sub_bind) \
	X("quat_real", glm_quat_real_bind) \
	X("quat_imag", glm_quat_imag_bind) \
	X("quat_imagn", glm_quat_imagn_bind) \
	X("quat_imaglen", glm_quat_imaglen_bind) \
	X("quat_angle", glm_quat_angle_bind) \
	X("quat_axis", glm_quat_axis_bind) \
	X("quat_mul", glm_quat_mul_bind) \
	X("quat_mat4", glm_quat_mat4_bind) \
	X("quat_mat4t", glm_quat_mat4t_bind) \
	X("quat_mat3", glm_quat_mat3_bind) \
	X("quat_mat3t", glm_quat_mat3t_bind) \
	X("quat_lerp", glm_quat_lerp_bind) \
	X("quat_nlerp", glm_quat_nlerp_bind) \
	X("quat_slerp", glm_quat_slerp_bind) \
	X("quat_look", glm_quat_look_bind) \
	X("quat_for", glm_quat_for_bind) \
	X("quat_forp", glm_quat_forp_bind) \
	X("quat_rotatev", glm_quat_rotatev_bind) \
	X("quat_rotate", glm_quat_rotate_bind) \
	X("quat_rotate_at", glm_quat_rotate_at_bind) \
	X("quat_rotate_atm", glm_quat_rotate_atm_bind) \
\
	/* mat2 */ \
	X("mat2_create", glm_mat2_create) \
	X("mat2_set", glm_mat2_set) \
	X("mat2_get", glm_mat2_get) \
	X("mat2_copy", glm_mat2_copy_bind) \
	X("mat2_identity", glm_mat2_identity_bind) \
	X("mat2_zero", glm_mat2_zero_bind) \
	X("mat2_mul", glm_mat2_mul_bind) \
	X("mat2_transpose_to", glm_mat2_transpose_to_bind) \
	X("mat2_transpose", glm_mat2_transpose_bind) \
	X("mat2_mulv", glm_mat2_mulv_bind) \
	X("mat2_scale", glm_mat2_scale_bind) \
	X("mat2_det", glm_mat2_det_bind) \
	X("mat2_inv", glm_mat2_inv_bind) \
	X("mat2_trace", glm_mat2_trace_bind) \
	X("mat2_swap_col", glm_mat2_swap_col_bind) \
	X("mat2_swap_row", glm_mat2_swap_row_bind) \
	X("mat2_rmc", glm_mat2_rmc_bind) \
\
	/* mat3 */ \
	X("mat3_create", glm_mat3_create) \
	X("mat3_set", glm_mat3_set) \
	X("mat3_get", glm_mat3_get) \
	X("mat3_copy", glm_mat3_copy_bind) \
	X("mat3_identity", glm_mat3_identity_bind) \
	X("mat3_zero", glm_mat3_zero_bind) \
	X("mat3_mul", glm_mat3_mul_bind) \
	X("mat3_transpose_to", glm_mat3_transpose_to_bind) \
	X("mat3_transpose", glm_mat3_transpose_bind) \
	X("mat3_mulv", glm_mat3_mulv_bind) \
	X("mat3_quat", glm_mat3_quat_bind) \
	X("mat3_scale", glm_mat3_scale_bind) \
	X("mat3_det", glm_mat3_det_bind) \
	X("mat3_inv", glm_mat3_inv_bind) \
	X("mat3_trace", glm_mat3_trace_bind) \
	X("mat3_swap_col", glm_mat3_swap_col_bind) \
	X("mat3_swap_row", glm_mat3_swap_row_bind) \
	X("mat3_rmc", glm_mat3_rmc_bind) \
\
	/* mat4 */ \
	X("mat4_create", glm_mat4_create) \
	X("mat4_set", glm_mat4_set) \
	X("mat4_get", glm_mat4_get) \
	X("mat4_ucopy", glm_mat4_ucopy_bind) \
	X("mat4_copy", glm_mat4_copy_bind) \
	X("mat4_identity", glm_mat4_identity_bind) \
	X("mat4_zero", glm_mat4_zero_bind) \
	X("mat4_pick3", glm_mat4_pick3_bind) \
	X("mat4_pick3t", glm_mat4_pick3t_bind) \
	X("mat4_ins3", glm_mat4_ins3_bind) \
	X("mat4_mul", glm_mat4_mul_bind) \
	X("mat4_mulv", glm_mat4_mulv_bind) \
	X("mat4_mulv3", glm_mat4_mulv3_bind) \
	X("mat4_trace", glm_mat4_trace_bind) \
	X("mat4_trace3", glm_mat4_trace3_bind) \
	X("mat4_quat", glm_mat4_quat_bind) \
	X("mat4_transpose_to", glm_mat4_transpose_to_bind) \
	X("mat4_transpose", glm_mat4_transpose_bind) \
	X("mat4_scale_p", glm_mat4_scale_p_bind) \
	X("mat4_scale", glm_mat4_scale_bind) \
	X("mat4_det", glm_mat4_det_bind) \
	X("mat4_inv", glm_mat4_inv_bind) \
	X("mat4_inv_fast", glm_mat4_inv_fast_bind) \
	X("mat4_swap_col", glm_mat4_swap_col_bind) \
	X("mat4_swap_row", glm_mat4_swap_row_bind) \
	X("mat4_rmc", glm_mat4_rmc_bind) \
\
	/* vec2 */ \
	X("vec2_create", glm_vec2_create) \
	X("vec2_set", glm_vec2_set) \
	X("vec2_get", glm_vec2_get) \
	X("vec2", glm_vec2_bind) \
	X("vec2_copy", glm_vec2_copy_bind) \
	X("vec2_zero", glm_vec2_zero_bind) \
	X("vec2_one", glm_vec2_one_bind) \
	X("vec2_dot", glm_vec2_dot_bind) \
	X("vec2_cross", glm_vec2_cross_bind) \
	X("vec2_norm2", glm_vec2_norm2_bind) \
	X("vec2_norm", glm_vec2_norm_bind) \
	X("vec2_add", glm_vec2_add_bind) \
	X("vec2_adds", glm_vec2_adds_bind) \
	X("vec2_sub", glm_vec2_sub_bind) \
	X("vec2_subs", glm_vec2_subs_bind) \
	X("vec2_mul", glm_vec2_mul_bind) \
	X("vec2_scale", glm_vec2_scale_bind) \
	X("vec2_scale_as", glm_vec2_scale_as_bind) \
	X("vec2_div", glm_vec2_div_bind) \
	X("vec2_divs", glm_vec2_divs_bind) \
	X("vec2_addadd", glm_vec2_addadd_bind) \
	X("vec2_subadd", glm_vec2_subadd_bind) \
	X("vec2_muladd", glm_vec2_muladd_bind) \
	X("vec2_muladds", glm_vec2_muladds_bind) \
	X("vec2_maxadd", glm_vec2_maxadd_bind) \
	X("vec2_minadd", glm_vec2_minadd_bind) \
	X("vec2_negate", glm_vec2_negate_bind) \
	X("vec2_negate_to", glm_vec2_negate_to_bind) \
	X("vec2_normalize", glm_vec2_normalize_bind) \
	X("vec2_normalize_to", glm_vec2_normalize_to_bind) \
	X("vec2_rotate", glm_vec2_rotate_bind) \
	X("vec2_distance2", glm_vec2_distance2_bind) \
	X("vec2_distance", glm_vec2_distance_bind) \
	X("vec2_maxv", glm_vec2_maxv_bind) \
	X("vec2_minv", glm_vec2_minv_bind) \
	X("vec2_clamp", glm_vec2_clamp_bind) \
	X("vec2_lerp", glm_vec2_lerp_bind) \
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
\
	/* vec4 */ \
	X("vec4_create", glm_vec4_create) \
	X("vec4_set", glm_vec4_set) \
	X("vec4_get", glm_vec4_get) \
	X("vec4", glm_vec4_bind) \
	X("vec4_copy3", glm_vec4_copy3_bind) \
	X("vec4_copy", glm_vec4_copy_bind) \
	X("vec4_ucopy", glm_vec4_ucopy_bind) \
	X("vec4_zero", glm_vec4_zero_bind) \
	X("vec4_dot", glm_vec4_dot_bind) \
	X("vec4_norm2", glm_vec4_norm2_bind) \
	X("vec4_norm", glm_vec4_norm_bind) \
	X("vec4_add", glm_vec4_add_bind) \
	X("vec4_adds", glm_vec4_adds_bind) \
	X("vec4_sub", glm_vec4_sub_bind) \
	X("vec4_subs", glm_vec4_subs_bind) \
	X("vec4_mul", glm_vec4_mul_bind) \
	X("vec4_scale", glm_vec4_scale_bind) \
	X("vec4_scale_as", glm_vec4_scale_as_bind) \
	X("vec4_div", glm_vec4_div_bind) \
	X("vec4_divs", glm_vec4_divs_bind) \
	X("vec4_addadd", glm_vec4_addadd_bind) \
	X("vec4_subadd", glm_vec4_subadd_bind) \
	X("vec4_muladd", glm_vec4_muladd_bind) \
	X("vec4_muladds", glm_vec4_muladds_bind) \
	X("vec4_maxadd", glm_vec4_maxadd_bind) \
	X("vec4_minadd", glm_vec4_minadd_bind) \
	X("vec4_flipsign", glm_vec4_flipsign_bind) \
	X("vec4_flipsign_to", glm_vec4_flipsign_to_bind) \
	X("vec4_inv", glm_vec4_inv_bind) \
	X("vec4_inv_to", glm_vec4_inv_to_bind) \
	X("vec4_negate", glm_vec4_negate_bind) \
	X("vec4_negate_to", glm_vec4_negate_to_bind) \
	X("vec4_normalize", glm_vec4_normalize_bind) \
	X("vec4_normalize_to", glm_vec4_normalize_to_bind) \
	X("vec4_distance", glm_vec4_distance_bind) \
	X("vec4_maxv", glm_vec4_maxv_bind) \
	X("vec4_minv", glm_vec4_minv_bind) \
	X("vec4_clamp", glm_vec4_clamp_bind) \
	X("vec4_lerp", glm_vec4_lerp_bind) \
	X("vec4_cubic", glm_vec4_cubic_bind) \


#define X(name, func) int func(lua_State *L);
GLM_FUNCTIONS
#undef X

#endif
