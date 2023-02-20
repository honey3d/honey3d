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


test("extract function name from signature", function()
	local name = b.ExtractFunctionName("int some_name(void *qqq);")
	assert(name == "some_name")
	name = b.ExtractFunctionName("float quitGame(int a, int b, int c, int** m);")
	assert(name == "quitGame")
	name = b.ExtractFunctionName("void startGame ();")
	assert(name == "startGame")
end)


test("extract function type from signature", function()
	local ftype = b.ExtractFunctionType("int some_ftype(void *qqq);")
	assert(ftype == "int")
	ftype = b.ExtractFunctionType("float quitGame(int a, int b, int c, int** m);")
	assert(ftype == "float")
	ftype = b.ExtractFunctionType("void startGame ();")
	assert(ftype == "void")
end)


test("extract arguments from signature", function()
	local args = b.ExtractFunctionArgs("int some_args(void *qqq);")
	assert(args ~= nil)
	assert(#args == 1)
	assert(args[1].type == "void *")
	assert(args[1].name == "qqq")

	args = b.ExtractFunctionArgs("float quitGame(int a, int b, int c, int** m);")
	assert(#args == 4)
	assert(args[1].type == "int")
	assert(args[1].name == "a")
	assert(args[2].type == "int")
	assert(args[2].name == "b")
	assert(args[3].type == "int")
	assert(args[3].name == "c")
	assert(args[4].type == "int **")
	assert(args[4].name == "m")

	args = b.ExtractFunctionArgs("void startGame ();")
	assert(#args == 0)
end)
