local b = {}
setmetatable(b, {__index=_G})
setfenv(1, b)


function ExtractFunctionName(signature)
	return string.match(signature, "([%w_][%w_]*)%s-%(.*%)")
end


function ExtractFunctionType(signature)
	return string.match(signature, "(.+)%s%s-[%w_]+%s-%(.*%)")
end


local function trimWhitespace(s)
	s = string.gsub(s, "^%s*", "")
	s = string.gsub(s, "%s+$", "")
	return s
end


function ExtractFunctionArgs(signature)
	local args = {}
	local argStr = string.match(signature, "%((.*)%)")
	for arg in string.gmatch(argStr, "([^,][^,]*),?") do
		-- handle pointers (e.g. void *q)
		arg = string.gsub(arg, "%*", " * ")

		local type = string.match(arg, "(.+)%s%s-[%w_]+")
		type = string.gsub(type, "%s%s+", " ")
		type = string.gsub(type, "%* %*", "**")
		type = trimWhitespace(type)

		local name = string.match(arg, "([%w_]+)%s-,?$")
		name = trimWhitespace(name)
		table.insert(args, { type=type, name=name })
	end
	return args
end


function GetPointerLevel(ctype)
	local level = 0
	for _ in string.gmatch(ctype, "%*") do
		level = level + 1
	end
	return level
end


function GetLuaType(ctype)
	-- double (triple, etc) pointers
	if GetPointerLevel(ctype) > 1 then return "unknown"
	-- regular pointers
	elseif GetPointerLevel(ctype) == 1  then
		-- strings
		if string.match(ctype, "char") then return "string"
		else return "unknown" end
	-- ordinary variables
	else
		-- numbers
		if     string.match(ctype, "float$") then return "number"
		elseif string.match(ctype, "double$") then return "number"
		-- integers
		elseif string.match(ctype, "char$") then return "integer"
		elseif string.match(ctype, "int$") then return "integer"
		elseif string.match(ctype, "long$") then return "integer"
		-- void
		elseif string.match(ctype, "void$") then return "void"
		-- unknown
		else return "unknown" end
	end
end


function PullArg(arg, index)
	local ltype = GetLuaType(arg.type)

	local pull
	if ltype == "unknown" then
		pull = string.format("/* get: %s */", arg.type)
	else
		pull = string.format("luaL_check%s(L, %d);", ltype, index)
	end

	return string.format("%s %s = %s", arg.type, arg.name, pull)
end


function Call(ftype, fname, args)
	local callArgs = "("
	for index, arg in ipairs(args) do
		callArgs = callArgs .. arg.name
		if index ~= #args then
			callArgs = callArgs .. ", "
		end
	end
	callArgs = callArgs .. ")"

	local ltype = GetLuaType(ftype)
	if ltype == "void" then
		return string.format("%s%s;\n\treturn 0;", fname, callArgs)
	elseif ltype == "unknown" then
		return string.format(
			"%s bind_result = %s%s;\n\t/* push result */\n\treturn /* count */;",
			ftype, fname, callArgs
		)
	else
		return string.format(
			"%s bind_result = %s%s;\n\tlua_push%s(L, bind_result);\n\treturn 1;",
			ftype, fname, callArgs, ltype
		)
	end
end


function bind(signature)
	local ftype = ExtractFunctionType(signature)
	local fname = ExtractFunctionName(signature)
	local args  = ExtractFunctionArgs(signature)

	local result = string.format("int %s_bind(lua_State *L)\n{\n", fname)
	for index, arg in ipairs(args) do
		result = result .. "\t" .. PullArg(arg, index) .. "\n"
	end

	result = result .. "\t" .. Call(ftype, fname, args) .. "\n}"
	return result
end


return b
