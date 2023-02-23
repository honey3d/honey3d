#!/usr/bin/lua5.1

local b = require 'generate-binding'


if arg[1] == "-f" then
	local signatures = {}
	local f = io.open(arg[2])
	for line in f:lines() do
		if string.match(line, "[^%s]") then
			table.insert(signatures, line)
		end
	end
	f:close()

	f = io.open(arg[2] .. ".bind", "w")
	for _, sig in ipairs(signatures) do
		local success, binding = pcall(b.bind, sig)
		if success == false then
			print(
				string.format(
					"bind signature \"%s\" failed: %s", sig, binding
				)
			)
		else
			f:write(b.bind(sig))
			f:write("\n\n\n")
		end
	end
	f:close()
else
	print(b.bind(arg[1]))
end
