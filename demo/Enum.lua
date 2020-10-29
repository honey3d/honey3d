local Enum = function (enumStrings)
    local enumTable = {}
    for _,str in pairs(enumStrings) do
	enumTable[str] = str
    end

    local enum = {}
    setmetatable(enum, { __index = enumTable,
			 __newindex = function(table, key, value)
			     error('Attempt to edit enum!')
			 end
		       }
    )
    
    return enum
end

return Enum
