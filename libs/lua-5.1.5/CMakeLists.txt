cmake_minimum_required(VERSION 3.2)
project(lua5.1)

set(LUA_ROOT ${lua5.1_SOURCE_DIR}/src)
add_library(lua5.1
	${LUA_ROOT}/lapi.c 
	${LUA_ROOT}/lcode.c 
	${LUA_ROOT}/ldebug.c 
	${LUA_ROOT}/ldo.c 
	${LUA_ROOT}/ldump.c 
	${LUA_ROOT}/lfunc.c 
	${LUA_ROOT}/lgc.c 
	${LUA_ROOT}/llex.c
	${LUA_ROOT}/lmem.c 
	${LUA_ROOT}/lobject.c 
	${LUA_ROOT}/lopcodes.c 
	${LUA_ROOT}/lparser.c 
	${LUA_ROOT}/lstate.c 
	${LUA_ROOT}/lstring.c
	${LUA_ROOT}/ltable.c 
	${LUA_ROOT}/ltm.c 
	${LUA_ROOT}/lundump.c 
	${LUA_ROOT}/lvm.c 
	${LUA_ROOT}/lzio.c
	${LUA_ROOT}/lauxlib.c 
	${LUA_ROOT}/lbaselib.c 
	${LUA_ROOT}/ldblib.c 
	${LUA_ROOT}/liolib.c 
	${LUA_ROOT}/lmathlib.c 
	${LUA_ROOT}/loslib.c
	${LUA_ROOT}/ltablib.c 
	${LUA_ROOT}/lstrlib.c 
	${LUA_ROOT}/loadlib.c 
	${LUA_ROOT}/linit.c)
