local Vec3 = {}

Vec3.prototype = {}

Vec3.prototype.dot = function(self, v)
    local result = Vec3.new{0,0,0}
    honey.cglm.vec3.dot(self.data, v.data, result.data)
    return result
end

Vec3.prototype.norm = function(self)
    return honey.cglm.vec3.norm(self.data)
end

Vec3.prototype.norm2 = function(self)
    return honey.cglm.vec3.norm2(self.data)
end

Vec3.prototype.add = function(self, v)
    local result = Vec3.new{0,0,0}
    honey.cglm.vec3.add(self.data, v.data, result.data)
    return result
end

Vec3.prototype.adds = function(self, s)
    local result = Vec3.new{0,0,0}
    honey.cglm.vec3.adds(self.data, s, result.data)
    return result
end

Vec3.prototype.mul = function(self, v)
    local result = Vec3.new{0,0,0}
    honey.cglm.vec3.mul(self.data, v.data, result.data)
    return result
end

Vec3.prototype.muls = function(self, s)
    local result = Vec3.new{0,0,0}
    honey.cglm.vec3.muls(self.data, s, result.data)
    return result
end

Vec3.prototype.normalize = function(self)
    honey.cglm.vec3.normalize(self.data)
end

Vec3.prototype.lerp = function(self, other, s)
    local result = Vec3.new{0,0,0}
    honey.cglm.vec3.lerp(self.data, other.data, s, result.data)
    return result
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vec3.mt = {}

Vec3.mt.__index = function(self, index)
    if type(index) == 'number' then
        return honey.cglm.get_value(self.data, index)
    else
        return Vec3.prototype[index]
    end
end

Vec3.mt.__newindex = function(self, index, value)
    if type(index) == 'number' then
        honey.cglm.set_value(self.data, index, value)
    else
        rawset(self, index, value)
    end
end

Vec3.mt.__tostring = function(vec3)
    local str = '['..
        tostring(self.data[0])..', '..
        tostring(self.data[1])..', '..
        tostring(self.data[2])..']'
    return str
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vec3.new = function(tbl)
    if #tbl ~= 3 then
        error('3-vectors require exactly three elements!')
    end
    
    local data = honey.cglm.new_array_zero(3)
    for i = 0,2 do
        honey.cglm.set_value(data, i, tbl[i+1])
    end

    local vec3 = {}
    vec3.data = data
    setmetatable(vec3, Vec3.mt)
    return vec3
end

return Vec3
    
