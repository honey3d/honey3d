local b = {}
setmetatable(b, {__index=G})
setfenv(1, b)


--===== enums =====--
local Enum = {}
-- create a single enum element
function Enum.new(name, id)
	local self = {
		name = string.upper(name),
		id = id,
	}
	setmetatable(self, Enum)
	return self
end
-- create multiple enums
function Enum.new_multi(tbl)
	local enums = {}
	for id, name in ipairs(tbl) do
		table.insert(enums, Enum.new(name, id))
	end
	return enums
end
-- make enums read-only
function Enum.__newindex(self)
	error("Attempted to set index on Enum")
end
-- make enums print nicely
function Enum.__tostring(self)
	return self.name
end
-- allow comparinge enums
function Enum.__eq(self, other)
	return self.id == other.id
end


local function check_match(string, pattern, rule)
	local match = string.match(string, '^' .. pattern)
	if match then
		return match, rule(match)
	end
end

local function append_match(string, pattern, rule, 


local function lex(string)
	for _, typename in ipairs(c_int_types) do
		if (string.sub(string, 1, #typename) == typename) then
			return 
	end
end


function bind(signature)
	
end


return b
