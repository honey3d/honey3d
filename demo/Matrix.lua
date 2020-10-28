local Mat3 = {}

Mat3.tostring = function(mat)
    local str = '[ ['..
        tostring(honey.cglm.get_value(mat, 0))..', '..
        tostring(honey.cglm.get_value(mat, 1))..', '..
        tostring(honey.cglm.get_value(mat, 2))..']\n  ['..
        tostring(honey.cglm.get_value(mat, 3))..', '..
        tostring(honey.cglm.get_value(mat, 4))..', '..
        tostring(honey.cglm.get_value(mat, 5))..']\n  ['..
        tostring(honey.cglm.get_value(mat, 6))..', '..
        tostring(honey.cglm.get_value(mat, 7))..', '..
        tostring(honey.cglm.get_value(mat, 8))..'] ]'
    return str
end

Mat3.new = function(tbl)
    if tbl == nil then
        return honey.cglm.new_array_zero(9)
    end
    
    if #tbl ~= 9 then
        error('3x3 matrices require exactly nine elements!')
    end
    
    local mat3 = honey.cglm.new_array_zero(9)
    for i = 0,8 do
        honey.cglm.set_value(mat3, i, tbl[i+1])
    end

    return mat3
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

local Mat4 = {}

Mat4.tostring = function(mat)
    local str = '[ ['..
        tostring(honey.cglm.get_value(mat, 0))..', '..
        tostring(honey.cglm.get_value(mat, 1))..', '..
        tostring(honey.cglm.get_value(mat, 2))..', '..
        tostring(honey.cglm.get_value(mat, 3))..']\n  ['..
        tostring(honey.cglm.get_value(mat, 4))..', '..
        tostring(honey.cglm.get_value(mat, 5))..', '..
        tostring(honey.cglm.get_value(mat, 6))..', '..
        tostring(honey.cglm.get_value(mat, 7))..']\n  ['..
        tostring(honey.cglm.get_value(mat, 8))..', '..
        tostring(honey.cglm.get_value(mat, 9))..', '..
        tostring(honey.cglm.get_value(mat, 10))..', '..
        tostring(honey.cglm.get_value(mat, 11))..']\n  ['..
        tostring(honey.cglm.get_value(mat, 12))..', '..
        tostring(honey.cglm.get_value(mat, 13))..', '..
        tostring(honey.cglm.get_value(mat, 14))..', '..
        tostring(honey.cglm.get_value(mat, 15))..'] ]'
    return str
end

Mat4.new = function(tbl)
    if tbl == nil then
        return honey.cglm.new_array_zero(16)
    end
    
    if #tbl ~= 16 then
        error('4x4 matrices require exactly 16 elements!')
    end
    
    local mat4 = honey.cglm.new_array_zero(16)
    for i = 0,15 do
        honey.cglm.set_value(mat4, i, tbl[i+1])
    end

    return mat4
end


return function() return Mat3, Mat4 end
