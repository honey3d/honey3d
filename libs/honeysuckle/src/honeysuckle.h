#ifndef HONEYSUCKLE_H
#define HONEYSUCKLE_H

#include <stdbool.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/* variadic macro argument counting */
#ifndef VA_NARGS

#define VA_NARGS(...) VA_NARGS_SHIFT_COUNT(__VA_ARGS__, VA_NARGS_COUNTS)

#define VA_NARGS_COUNTS				\
  255, 254, 253, 252, 251, 250, 249, 248,	\
    247, 246, 245, 244, 243, 242, 241, 240,	\
    239, 238, 237, 236, 235, 234, 233, 232,	\
    231, 230, 229, 228, 227, 226, 225, 224,	\
    223, 222, 221, 220, 219, 218, 217, 216,	\
    215, 214, 213, 212, 211, 210, 209, 208,	\
    207, 206, 205, 204, 203, 202, 201, 200,	\
    199, 198, 197, 196, 195, 194, 193, 192,	\
    191, 190, 189, 188, 187, 186, 185, 184,	\
    183, 182, 181, 180, 179, 178, 177, 176,	\
    175, 174, 173, 172, 171, 170, 169, 168,	\
    167, 166, 165, 164, 163, 162, 161, 160,	\
    159, 158, 157, 156, 155, 154, 153, 152,	\
    151, 150, 149, 148, 147, 146, 145, 144,	\
    143, 142, 141, 140, 139, 138, 137, 136,	\
    135, 134, 133, 132, 131, 130, 129, 128,	\
    127, 126, 125, 124, 123, 122, 121, 120,	\
    119, 118, 117, 116, 115, 114, 113, 112,	\
    111, 110, 109, 108, 107, 106, 105, 104,	\
    103, 102, 101, 100, 99, 98, 97, 96,		\
    95, 94, 93, 92, 91, 90, 89, 88,		\
    87, 86, 85, 84, 83, 82, 81, 80,		\
    79, 78, 77, 76, 75, 74, 73, 72,		\
    71, 70, 69, 68, 67, 66, 65, 64,		\
    63, 62, 61, 60, 59, 58, 57, 56,		\
    55, 54, 53, 52, 51, 50, 49, 48,		\
    47, 46, 45, 44, 43, 42, 41, 40,		\
    39, 38, 37, 36, 35, 34, 33, 32,		\
    31, 30, 29, 28, 27, 26, 25, 24,		\
    23, 22, 21, 20, 19, 18, 17, 16,		\
    15, 14, 13, 12, 11, 10, 9, 8,		\
    7, 6, 5, 4, 3, 2, 1, 0

#define VA_NARGS_GET_COUNT(					\
		       _255, _254, _253, _252, _251, _250, _249, _248,	\
		       _247, _246, _245, _244, _243, _242, _241, _240,	\
		       _239, _238, _237, _236, _235, _234, _233, _232,	\
		       _231, _230, _229, _228, _227, _226, _225, _224,	\
		       _223, _222, _221, _220, _219, _218, _217, _216,	\
		       _215, _214, _213, _212, _211, _210, _209, _208,	\
		       _207, _206, _205, _204, _203, _202, _201, _200,	\
		       _199, _198, _197, _196, _195, _194, _193, _192,	\
		       _191, _190, _189, _188, _187, _186, _185, _184,	\
		       _183, _182, _181, _180, _179, _178, _177, _176,	\
		       _175, _174, _173, _172, _171, _170, _169, _168,	\
		       _167, _166, _165, _164, _163, _162, _161, _160,	\
		       _159, _158, _157, _156, _155, _154, _153, _152,	\
		       _151, _150, _149, _148, _147, _146, _145, _144,	\
		       _143, _142, _141, _140, _139, _138, _137, _136,	\
		       _135, _134, _133, _132, _131, _130, _129, _128,	\
		       _127, _126, _125, _124, _123, _122, _121, _120,	\
		       _119, _118, _117, _116, _115, _114, _113, _112,	\
		       _111, _110, _109, _108, _107, _106, _105, _104,	\
		       _103, _102, _101, _100, _99, _98, _97, _96,	\
		       _95, _94, _93, _92, _91, _90, _89, _88,		\
		       _87, _86, _85, _84, _83, _82, _81, _80,		\
		       _79, _78, _77, _76, _75, _74, _73, _72,		\
		       _71, _70, _69, _68, _67, _66, _65, _64,		\
		       _63, _62, _61, _60, _59, _58, _57, _56,		\
		       _55, _54, _53, _52, _51, _50, _49, _48,		\
		       _47, _46, _45, _44, _43, _42, _41, _40,		\
		       _39, _38, _37, _36, _35, _34, _33, _32,		\
		       _31, _30, _29, _28, _27, _26, _25, _24,		\
		       _23, _22, _21, _20, _19, _18, _17, _16,		\
		       _15, _14, _13, _12, _11, _10, _9, _8,		\
		       _7, _6, _5, _4, _3, _2, _1, N, ...) N

#define VA_NARGS_SHIFT_COUNT(...) VA_NARGS_GET_COUNT(__VA_ARGS__)

#endif


/* type constants */
typedef enum
  { HS_BOOL,
    HS_INT,
    HS_NUM,
    HS_STR,
    HS_TBL,
    HS_FUNC,
    HS_CFUNC,
    HS_USER,
    HS_LIGHT,
    HS_NIL,
    HS_ANY,
  } hs_type;

const char* hs_type_to_string(hs_type type);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * hs_parse_args and hs_parse_overloaded
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

struct hs_arg {
  hs_type type;
  union {
    bool *boolean;
    lua_Integer *integer;
    lua_Number *number;
    char **string;
    int *stack_index;
    lua_CFunction *function;
    void **userdata;
  } ptr;
};

#define hs_bool(x)  { .type=HS_BOOL,  .ptr.boolean = &(x) }
#define hs_int(x)   { .type=HS_INT,   .ptr.integer = &(x) }
#define hs_num(x)   { .type=HS_NUM,   .ptr.number = &(x) }
#define hs_str(x)   { .type=HS_STR,   .ptr.string = &(x) }
#define hs_tbl(x)   { .type=HS_TBL,   .ptr.stack_index = &(x) }
#define hs_func(x)  { .type=HS_FUNC,  .ptr.stack_index = &(x) }
#define hs_cfunc(x) { .type=HS_CFUNC, .ptr.function = &(x) }
#define hs_user(x)  { .type=HS_USER,  .ptr.userdata = &(x) }
#define hs_light(x) { .type=HS_LIGHT, .ptr.userdata = &(x) }
#define hs_nil(x)   { .type=HS_NIL,   .ptr.stack_index = &(x) }
#define hs_any(x)   { .type=HS_ANY,   .ptr.stack_index = &(x) }

void hs_parse_args_(lua_State *L, int n_args, struct hs_arg *arguments);

#define hs_parse_args(L, ...)				\
   hs_parse_args_(L,					\
		  VA_NARGS(__VA_ARGS__)/2,		\
		 (struct hs_arg[]) { __VA_ARGS__ })


#define hs_overload(...) VA_NARGS(__VA_ARGS__)/2, (struct hs_arg[]) { __VA_ARGS__ }

int hs_parse_overloaded_(lua_State *L, ...);

#define hs_parse_overloaded(L, ...)		\
   hs_parse_overloaded_(L, __VA_ARGS__, -1)

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * hs_create_table
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

typedef union {
   bool boolean;
   lua_Integer integer;
   lua_Number number;
   char *string;
   int stack_index;
   lua_CFunction function;
   void *userdata;
} hs_value;

struct hs_tbl_entry {
   hs_type key_type;
   hs_value key;
   hs_type value_type;
   hs_value value;
};

#define hs_bool_bool(k, v)				\
   { .key_type=HS_BOOL, .key.boolean=k,			\
	 .value_type=HS_BOOL, .value.boolean=v }
#define hs_bool_int(k, v)			\
   { .key_type=HS_BOOL, .key.boolean=k,		\
	 .value_type=HS_INT, .value.integer=v }
#define hs_bool_num(k, v)			\
   { .key_type=HS_BOOL, .key.boolean=k,		\
	 .value_type=HS_NUM, .value.number=v }
#define hs_bool_str(k, v)			\
   { .key_type=HS_BOOL, .key.boolean=k,		\
	 .value_type=HS_STR, .value.string=v }
#define hs_bool_tbl(k, v)				\
   { .key_type=HS_BOOL, .key.boolean=k,			\
	 .value_type=HS_TBL, .value.stack_index=v }
#define hs_bool_func(k, v)				\
   { .key_type=HS_BOOL, .key.boolean=k,			\
	 .value_type=HS_FUNC, .value.stack_index=v }
#define hs_bool_cfunc(k, v)				\
   { .key_type=HS_BOOL, .key.boolean=k,			\
	 .value_type=HS_CFUNC, .value.function=v }
#define hs_bool_user(k, v)				\
   { .key_type=HS_BOOL, .key.boolean=k,			\
	 .value_type=HS_USER, .value.stack_index=v }
#define hs_bool_light(k, v)				\
   { .key_type=HS_BOOL, .key.boolean=k,			\
	 .value_type=HS_LIGHT, .value.userdata=v }

#define hs_int_bool(k, v)				\
   { .key_type=HS_INT, .key.integer=k,			\
	 .value_type=HS_BOOL, .value.boolean=v }
#define hs_int_int(k, v)			\
   { .key_type=HS_INT, .key.integer=k,		\
	 .value_type=HS_INT, .value.integer=v }
#define hs_int_num(k, v)			\
   { .key_type=HS_INT, .key.integer=k,		\
	 .value_type=HS_NUM, .value.number=v }
#define hs_int_str(k, v)			\
   { .key_type=HS_INT, .key.integer=k,		\
	 .value_type=HS_STR, .value.string=v }
#define hs_int_tbl(k, v)			\
   { .key_type=HS_INT, .key.integer=k,		\
	 .value_type=HS_TBL, .value.stack_index=v }
#define hs_int_func(k, v)			\
   { .key_type=HS_INT, .key.integer=k,		\
	 .value_type=HS_FUNC, .value.stack_index=v }
#define hs_int_cfunc(k, v)			\
   { .key_type=HS_INT, .key.integer=k,		\
	 .value_type=HS_CFUNC, .value.function=v }
#define hs_int_user(k, v)			\
   { .key_type=HS_INT, .key.integer=k,		\
	 .value_type=HS_USER, .value.stack_index=v }
#define hs_int_light(k, v)			\
   { .key_type=HS_INT, .key.integer=k,		\
	 .value_type=HS_LIGHT, .value.userdata=v }
   
#define hs_num_bool(k, v)			\
   { .key_type=HS_NUM, .key.number=k,		\
	 .value_type=HS_BOOL, .value.boolean=v }
#define hs_num_int(k, v)			\
   { .key_type=HS_NUM, .key.number=k,		\
	 .value_type=HS_INT, .value.integer=v }
#define hs_num_num(k, v)			\
   { .key_type=HS_NUM, .key.number=k,		\
	 .value_type=HS_NUM, .value.number=v }
#define hs_num_str(k, v)			\
   { .key_type=HS_NUM, .key.number=k,		\
	 .value_type=HS_STR, .value.string=v }
#define hs_num_tbl(k, v)			\
   { .key_type=HS_NUM, .key.number=k,		\
	 .value_type=HS_TBL, .value.stack_index=v }
#define hs_num_func(k, v)			\
   { .key_type=HS_NUM, .key.number=k,		\
	 .value_type=HS_FUNC, .value.stack_index=v }
#define hs_num_cfunc(k, v)			\
   { .key_type=HS_NUM, .key.number=k,		\
	 .value_type=HS_CFUNC, .value.function=v }
#define hs_num_user(k, v)			\
   { .key_type=HS_NUM, .key.number=k,		\
	 .value_type=HS_USER, .value.stack_index=v }
#define hs_num_light(k, v)			\
   { .key_type=HS_NUM, .key.number=k,		\
	 .value_type=HS_LIGHT, .value.userdata=v }

#define hs_str_bool(k, v)			\
   { .key_type=HS_STR, .key.string=k,		\
	 .value_type=HS_BOOL, .value.boolean=v }
#define hs_str_int(k, v)			\
   { .key_type=HS_STR, .key.string=k,		\
	 .value_type=HS_INT, .value.integer=v }
#define hs_str_num(k, v)			\
   { .key_type=HS_STR, .key.string=k,		\
	 .value_type=HS_NUM, .value.number=v }
#define hs_str_str(k, v)			\
   { .key_type=HS_STR, .key.string=k,		\
	 .value_type=HS_STR, .value.string=v }
#define hs_str_tbl(k, v)			\
   { .key_type=HS_STR, .key.string=k,		\
	 .value_type=HS_TBL, .value.stack_index=v }
#define hs_str_func(k, v)			\
   { .key_type=HS_STR, .key.string=k,		\
	 .value_type=HS_FUNC, .value.stack_index=v }
#define hs_str_cfunc(k, v)			\
   { .key_type=HS_STR, .key.string=k,		\
	 .value_type=HS_CFUNC, .value.function=v }
#define hs_str_user(k, v)			\
   { .key_type=HS_STR, .key.string=k,		\
	 .value_type=HS_USER, .value.stack_index=v }
#define hs_str_light(k, v)			\
   { .key_type=HS_STR, .key.string=k,		\
	 .value_type=HS_LIGHT, .value.userdata=v }


#define hs_tbl_bool(k, v)			\
   { .key_type=HS_TBL, .key.stack_index=k,	\
	 .value_type=HS_BOOL, .value.boolean=v }
#define hs_tbl_int(k, v)			\
   { .key_type=HS_TBL, .key.stack_index=k,	\
	 .value_type=HS_INT, .value.integer=v }
#define hs_tbl_num(k, v)			\
   { .key_type=HS_TBL, .key.stack_index=k,	\
	 .value_type=HS_NUM, .value.number=v }
#define hs_tbl_str(k, v)			\
   { .key_type=HS_TBL, .key.stack_index=k,	\
	 .value_type=HS_STR, .value.string=v }
#define hs_tbl_tbl(k, v)			\
   { .key_type=HS_TBL, .key.stack_index=k,	\
	 .value_type=HS_TBL, .value.stack_index=v }
#define hs_tbl_func(k, v)			\
   { .key_type=HS_TBL, .key.stack_index=k,	\
	 .value_type=HS_FUNC, .value.stack_index=v }
#define hs_tbl_cfunc(k, v)			\
   { .key_type=HS_TBL, .key.stack_index=k,	\
	 .value_type=HS_CFUNC, .value.function=v }
#define hs_tbl_user(k, v)			\
   { .key_type=HS_TBL, .key.stack_index=k,	\
	 .value_type=HS_USER, .value.stack_index=v }
#define hs_tbl_light(k, v)			\
   { .key_type=HS_TBL, .key.stack_index=k,	\
	 .value_type=HS_LIGHT, .value.userdata=v }

#define hs_func_bool(k, v)			\
   { .key_type=HS_FUNC, .key.stack_index=k,	\
	 .value_type=HS_BOOL, .value.boolean=v }
#define hs_func_int(k, v)			\
   { .key_type=HS_FUNC, .key.stack_index=k,	\
	 .value_type=HS_INT, .value.integer=v }
#define hs_func_num(k, v)			\
   { .key_type=HS_FUNC, .key.stack_index=k,	\
	 .value_type=HS_NUM, .value.number=v }
#define hs_func_str(k, v)			\
   { .key_type=HS_FUNC, .key.stack_index=k,	\
	 .value_type=HS_STR, .value.string=v }
#define hs_func_tbl(k, v)			\
   { .key_type=HS_FUNC, .key.stack_index=k,	\
	 .value_type=HS_TBL, .value.stack_index=v }
#define hs_func_func(k, v)			\
   { .key_type=HS_FUNC, .key.stack_index=k,	\
	 .value_type=HS_FUNC, .value.stack_index=v }
#define hs_func_cfunc(k, v)			\
   { .key_type=HS_FUNC, .key.stack_index=k,	\
	 .value_type=HS_CFUNC, .value.function=v }
#define hs_func_user(k, v)			\
   { .key_type=HS_FUNC, .key.stack_index=k,	\
	 .value_type=HS_USER, .value.stack_index=v }
#define hs_func_light(k, v)			\
   { .key_type=HS_FUNC, .key.stack_index=k,	\
	 .value_type=HS_LIGHT, .value.userdata=v }

#define hs_cfunc_bool(k, v)			\
   { .key_type=HS_CFUNC, .key.function=k,	\
	 .value_type=HS_BOOL, .value.boolean=v }
#define hs_cfunc_int(k, v)			\
   { .key_type=HS_CFUNC, .key.function=k,	\
	 .value_type=HS_INT, .value.integer=v }
#define hs_cfunc_num(k, v)			\
   { .key_type=HS_CFUNC, .key.function=k,	\
	 .value_type=HS_NUM, .value.number=v }
#define hs_cfunc_str(k, v)			\
   { .key_type=HS_CFUNC, .key.function=k,	\
	 .value_type=HS_STR, .value.string=v }
#define hs_cfunc_tbl(k, v)			\
   { .key_type=HS_CFUNC, .key.function=k,	\
	 .value_type=HS_TBL, .value.stack_index=v }
#define hs_cfunc_func(k, v)			\
   { .key_type=HS_CFUNC, .key.function=k,	\
	 .value_type=HS_FUNC, .value.stack_index=v }
#define hs_cfunc_cfunc(k, v)			\
   { .key_type=HS_CFUNC, .key.function=k,	\
	 .value_type=HS_CFUNC, .value.function=v }
#define hs_cfunc_user(k, v)			\
   { .key_type=HS_CFUNC, .key.function=k,	\
	 .value_type=HS_USER, .value.stack_index=v }
#define hs_cfunc_light(k, v)			\
   { .key_type=HS_CFUNC, .key.function=k,	\
	 .value_type=HS_LIGHT, .value.userdata=v }
   
#define hs_user_bool(k, v)			\
   { .key_type=HS_USER, .key.stack_index=k,	\
	 .value_type=HS_BOOL, .value.boolean=v }
#define hs_user_int(k, v)			\
   { .key_type=HS_USER, .key.stack_index=k,	\
	 .value_type=HS_INT, .value.integer=v }
#define hs_user_num(k, v)			\
   { .key_type=HS_USER, .key.stack_index=k,	\
	 .value_type=HS_NUM, .value.number=v }
#define hs_user_str(k, v)			\
   { .key_type=HS_USER, .key.stack_index=k,	\
	 .value_type=HS_STR, .value.string=v }
#define hs_user_tbl(k, v)			\
   { .key_type=HS_USER, .key.stack_index=k,	\
	 .value_type=HS_TBL, .value.stack_index=v }
#define hs_user_func(k, v)			\
   { .key_type=HS_USER, .key.stack_index=k,	\
	 .value_type=HS_FUNC, .value.stack_index=v }
#define hs_user_cfunc(k, v)			\
   { .key_type=HS_USER, .key.stack_index=k,	\
	 .value_type=HS_CFUNC, .value.function=v }
#define hs_user_user(k, v)			\
   { .key_type=HS_USER, .key.stack_index=k,	\
	 .value_type=HS_USER, .value.stack_index=v }
#define hs_user_light(k, v)			\
   { .key_type=HS_USER, .key.stack_index=k,	\
	 .value_type=HS_LIGHT, .value.userdata=v }

#define hs_light_bool(k, v)			\
   { .key_type=HS_LIGHT, .key.userdata=k,	\
	 .value_type=HS_BOOL, .value.boolean=v }
#define hs_light_int(k, v)			\
   { .key_type=HS_LIGHT, .key.userdata=k,	\
	 .value_type=HS_INT, .value.integer=v }
#define hs_light_num(k, v)			\
   { .key_type=HS_LIGHT, .key.userdata=k,	\
	 .value_type=HS_NUM, .value.number=v }
#define hs_light_str(k, v)			\
   { .key_type=HS_LIGHT, .key.userdata=k,	\
	 .value_type=HS_STR, .value.string=v }
#define hs_light_tbl(k, v)			\
   { .key_type=HS_LIGHT, .key.userdata=k,	\
	 .value_type=HS_TBL, .value.stack_index=v }
#define hs_light_func(k, v)			\
   { .key_type=HS_LIGHT, .key.userdata=k,	\
	 .value_type=HS_FUNC, .value.stack_index=v }
#define hs_light_cfunc(k, v)			\
   { .key_type=HS_LIGHT, .key.userdata=k,	\
	 .value_type=HS_CFUNC, .value.function=v }
#define hs_light_user(k, v)			\
   { .key_type=HS_LIGHT, .key.userdata=k,	\
	 .value_type=HS_USER, .value.stack_index=v }
#define hs_light_light(k, v)			\
   { .key_type=HS_LIGHT, .key.userdata=k,	\
	 .value_type=HS_LIGHT, .value.userdata=v }
   
int hs_create_table_(lua_State *L, int n_elements, struct hs_tbl_entry *elements);

#define hs_create_table(L, ...)					\
   hs_create_table_(L,						\
		    VA_NARGS(__VA_ARGS__)/4,			\
		    (struct hs_tbl_entry[]) { __VA_ARGS__ })


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * hs_process_table
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

typedef void (*hs_pt_bool_callback)(bool, void *);
typedef void (*hs_pt_int_callback)(lua_Integer, void *);
typedef void (*hs_pt_num_callback)(lua_Number, void *);
typedef void (*hs_pt_str_callback)(const char *, void *);


// default processors
void hs_pt_set_boolean(bool value, void *data);
void hs_pt_set_integer(lua_Integer value, void *data);
void hs_pt_set_number(lua_Number value, void *data);
void hs_pt_set_string(const char *value, void *data);


struct hs_table_processor {
   const char *key;
   hs_type type;
   union {
      hs_pt_bool_callback boolean;
      hs_pt_int_callback integer;
      hs_pt_num_callback number;
      hs_pt_str_callback string;
   } func;
   void *data;
};

#define hs_process_bool(str, f, d)				\
   { .key=(str), .type=HS_BOOL, .func.boolean=(f), .data=(d) }
#define hs_process_int(str, f, d)				\
   { .key=(str), .type=HS_INT, .func.integer=(f), .data=(d) }
#define hs_process_num(str, f, d)				\
   { .key=(str), .type=HS_NUM, .func.number=(f), .data=(d) }
#define hs_process_str(str, f, d)				\
   { .key=(str), .type=HS_STR, .func.string=(f), .data=(d) }

void hs_process_table_(lua_State *L,
		       int table_index,
		       int n_processors,
		       struct hs_table_processor *processors);

#define hs_process_table(L, table_index, ...)	\
   hs_process_table_(L, table_index, \
		     VA_NARGS(__VA_ARGS__)/4, \
		     (struct hs_table_processor[]) {__VA_ARGS__})


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * hs_pushstring
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void hs_vpushstring(lua_State *L, const char *format_string, va_list args);
void hs_pushstring(lua_State *L, const char *format_string, ...);


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * error creation and handling
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void hs_throw_error(lua_State *L, const char *format_string, ...);
int hs_traceback(lua_State *L);
int hs_call(lua_State *L, int nargs, int nret);


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * registry operations
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#define hs_rstore(L) luaL_ref(L, LUA_REGISTRYINDEX);
#define hs_rload(L, ref) lua_rawgeti(L, LUA_REGISTRYINDEX, ref)
#define hs_rdel(L, ref) luaL_unref(L, LUA_REGISTRYINDEX, ref)

#endif
