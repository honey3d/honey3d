local Vec3 = {}

Vec3.tostring = function(vec3)
    local str = '['..
        tostring(honey.cglm.get_value(vec3, 0))..','..
        tostring(honey.cglm.get_value(vec3, 1))..','..
        tostring(honey.cglm.get_value(vec3, 2))..']'
    return str
end

Vec3.new = function(tbl)
    if tbl == nil then
        return honey.cglm.new_array_zero(3)
    end
    
    if #tbl ~= 3 then
        error('3-vectors require exactly three elements!')
    end
    
    local vec3 = honey.cglm.new_array_zero(3)
    for i = 0,2 do
        honey.cglm.set_value(vec3, i, tbl[i+1])
    end

    return vec3
end

Vec3.ZERO   = Vec3.new()
Vec3.X_UNIT = Vec3.new{1, 0, 0}
Vec3.Y_UNIT = Vec3.new{0, 1, 0}
Vec3.Z_UNIT = Vec3.new{0, 0, 1}

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

local Vec4 = {}

Vec4.tostring = function(vec4)
    local str = '['..
        tostring(honey.cglm.get_value(vec4, 0))..','..
        tostring(honey.cglm.get_value(vec4, 1))..','..
        tostring(honey.cglm.get_value(vec4, 2))..','..
        tostring(honey.cglm.get_value(vec4, 3))..']'
    return str
end

Vec4.new = function(tbl)
    if tbl == nil then
        return honey.cglm.new_array_zero(4)
    end
    
    if #tbl ~= 4 then
        error('4-vectors require exactly four elements!')
    end
    
    local vec4 = honey.cglm.new_array_zero(4)
    for i = 0,3 do
        honey.cglm.set_value(vec4, i, tbl[i+1])
    end

    return vec4
end


return function() return Vec3, Vec4 end

