local Mat3 = {}

Mat3.index = function(i, j)
    return (i-1) + 3*(j-1)
end

Mat3.tostring = function(mat)
    local str = '[ ['..
        tostring(honey.cglm.get_value(mat, 0))..', '..
        tostring(honey.cglm.get_value(mat, 3))..', '..
        tostring(honey.cglm.get_value(mat, 6))..']\n  ['..
        tostring(honey.cglm.get_value(mat, 1))..', '..
        tostring(honey.cglm.get_value(mat, 4))..', '..
        tostring(honey.cglm.get_value(mat, 7))..']\n  ['..
        tostring(honey.cglm.get_value(mat, 2))..', '..
        tostring(honey.cglm.get_value(mat, 5))..', '..
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

Mat4.index = function(i, j)
    return (i-1) + 4*(j-1)
end

Mat4.tostring = function(matrix)
    str = ''
    for i = 1,4 do
        for j = 1,4 do
            str = str..tostring(honey.cglm.get_value(matrix, Mat4.index(i,j)))..', '
        end
        str = str..'\n'
    end
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
    honey.cglm.set_value(mat4, 0, tbl[1])
    honey.cglm.set_value(mat4, 1, tbl[5])
    honey.cglm.set_value(mat4, 2, tbl[9])
    honey.cglm.set_value(mat4, 3, tbl[13])
    honey.cglm.set_value(mat4, 4, tbl[2])
    honey.cglm.set_value(mat4, 5, tbl[6])
    honey.cglm.set_value(mat4, 6, tbl[10])
    honey.cglm.set_value(mat4, 7, tbl[14])
    honey.cglm.set_value(mat4, 8, tbl[3])
    honey.cglm.set_value(mat4, 9, tbl[7])
    honey.cglm.set_value(mat4, 10, tbl[11])
    honey.cglm.set_value(mat4, 11, tbl[15])
    honey.cglm.set_value(mat4, 12, tbl[4])
    honey.cglm.set_value(mat4, 13, tbl[8])
    honey.cglm.set_value(mat4, 14, tbl[12])
    honey.cglm.set_value(mat4, 15, tbl[16])

    setmetatable(mat4, Mat4.mt)

    return mat4
end


return function() return Mat3, Mat4 end
