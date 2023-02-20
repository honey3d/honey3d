function test(description, func)
	io.write(description .. ': ')
	local result, msg = pcall(func)
	if result == true then
		print("OK")
	else
		print("FAIL")
		print(debug.traceback(msg))
		print()
	end
end


local b = require 'generate-binding'


test("simplest possible binding", function()
	local binding = b.bind("void some_function();")
	assert(binding == [[
int some_function_bind(lua_State *L)
{
	some_function();
	return 0;
}]])
end)


test("complicated binding", function()
	local binding = b.bind("const char * qqq(int a, float q, unsigned char m);")
	assert(binding == [[
int qqq_bind(lua_State *L)
{
	lua_Integer a = luaL_checkinteger(L, 1);
	lua_Number q = luaL_checknumber(L, 2);
	lua_Integer m = luaL_checkinteger(L, 3);
	const char *result = qqq(a, q, m);
	lua_pushstring(L, result);
	return 1;
}]])
end)
