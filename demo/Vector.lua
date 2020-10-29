local Enum = require('Enum')

local Vector = {}

Vector.type = Enum{'Vec3', 'Vec4'}

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
--
-- Vec3
--
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vector.Vec3 = {}

Vector.Vec3.prototype = {}

Vector.Vec3.prototype.type = Vector.type.Vec3

Vector.Vec3.prototype.at = function(self, index)
   return honey.cglm.get_value(self.array, index)
end

Vector.Vec3.prototype.setAt = function(self, index, value)
   honey.cglm.set_value(self.array, index, value)
end

Vector.Vec3.prototype.dot = function(self, v, dest)
   local result
   if dest == nil then
      result = Vector.Vec3.new()
   else
      result = dest
   end

   honey.cglm.vec3.dot(self.array, v.array, result.array)
   return result
end

Vector.Vec3.prototype.norm2 = function(self)
   return honey.cglm.vec3.norm2(self.array)
end

Vector.Vec3.prototype.norm = function(self)
   return honey.cglm.vec3.norm(self.array)
end

Vector.Vec3.prototype.add = function(self, v, dest)
   local result
   if dest == nil then
      result = Vector.Vec3.new()
   else
      result = dest
   end

   honey.cglm.vec3.add(self.array, v.array, result.array)
   return result
end

Vector.Vec3.prototype.adds = function(self, s, dest)
   local result
   if dest == nil then
      result = Vector.Vec3.new()
   else
      result = dest
   end

   honey.cglm.vec3.adds(s, self.array, result.array)
   return result
end

Vector.Vec3.prototype.sub = function(self, v, dest)
   local result
   if dest == nil then
      result = Vector.Vec3.new()
   else
      result = dest
   end

   honey.cglm.vec3.sub(self.array, v.array, result.array)
   return result
end

Vector.Vec3.prototype.mul = function(self, v, dest)
   local result
   if dest == nil then
      result = Vector.Vec3.new()
   else
      result = dest
   end

   honey.cglm.vec3.mul(self.array, v.array, result.array)
   return result
end

Vector.Vec3.prototype.muls = function(self, s, dest)
   local result
   if dest == nil then
      result = Vector.Vec3.new()
   else
      result = dest
   end

   honey.cglm.vec3.muls(s, self.array, result.array)
   return result
end

Vector.Vec3.prototype.normalize = function(self)
   honey.cglm.vec3.normalize(self.array)
end

Vector.Vec3.prototype.distanceTo = function(self, v)
   return honey.cglm.vec3.distance(self.array, v.array)
end

Vector.Vec3.prototype.lerp = function(self, v, s, dest)
   local result
   if dest == nil then
      result = Vector.Vec3.new()
   else
      result = dest
   end

   honey.cglm.vec3.lerp(self.array, v.array, s, result.array)
   return result
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vector.Vec3.mt = {}
Vector.Vec3.mt.__index = Vector.Vec3.prototype
Vector.Vec3.mt.__tostring = function(vec3)
   local str = 'vec3('..
      tostring(vec3:at(0))..', '..
      tostring(vec3:at(1))..', '..
      tostring(vec3:at(2))..')'
   return str
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vector.Vec3.new = function(tbl)
   local vec3 = {}
   vec3.array = honey.cglm.new_array_zero(3)
   setmetatable(vec3, Vector.Vec3.mt)

   if tbl == nil then return vec3 end

   for i=0,2 do
      vec3:setAt(i, tbl[i+1])
   end

   return vec3
end

Vector.Vec3.ZERO = Vector.Vec3.new()
Vector.Vec3.X_UNIT = Vector.Vec3.new{1, 0, 0}
Vector.Vec3.Y_UNIT = Vector.Vec3.new{0, 1, 0}
Vector.Vec3.Z_UNIT = Vector.Vec3.new{0, 0, 1}

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
--
-- Vec4
--
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vector.Vec4 = {}

Vector.Vec4.prototype = {}

Vector.Vec4.prototype.type = Vector.type.Vec4

Vector.Vec4.prototype.at = function(self, index)
   return honey.cglm.get_value(self.array, index)
end

Vector.Vec4.prototype.setAt = function(self, index, value)
   honey.cglm.set_value(self.array, index, value)
end

Vector.Vec4.prototype.dot = function(self, v, dest)
   local result
   if dest == nil then
      result = Vector.Vec4.new()
   else
      result = dest
   end

   honey.cglm.vec4.dot(self.array, v.array, result.array)
   return result
end

Vector.Vec4.prototype.norm2 = function(self)
   return honey.cglm.vec4.norm2(self.array)
end

Vector.Vec4.prototype.norm = function(self)
   return honey.cglm.vec4.norm(self.array)
end

Vector.Vec4.prototype.add = function(self, v, dest)
   local result
   if dest == nil then
      result = Vector.Vec4.new()
   else
      result = dest
   end

   honey.cglm.vec4.add(self.array, v.array, result.array)
   return result
end

Vector.Vec4.prototype.adds = function(self, s, dest)
   local result
   if dest == nil then
      result = Vector.Vec4.new()
   else
      result = dest
   end

   honey.cglm.vec4.adds(s, self.array, result.array)
   return result
end

Vector.Vec4.prototype.sub = function(self, v, dest)
   local result
   if dest == nil then
      result = Vector.Vec4.new()
   else
      result = dest
   end

   honey.cglm.vec4.sub(self.array, v.array, result.array)
   return result
end

Vector.Vec4.prototype.mul = function(self, v, dest)
   local result
   if dest == nil then
      result = Vector.Vec4.new()
   else
      result = dest
   end

   honey.cglm.vec4.mul(self.array, v.array, result.array)
   return result
end

Vector.Vec4.prototype.muls = function(self, s, dest)
   local result
   if dest == nil then
      result = Vector.Vec4.new()
   else
      result = dest
   end

   honey.cglm.vec4.muls(s, self.array, result.array)
   return result
end

Vector.Vec4.prototype.normalize = function(self)
   honey.cglm.vec4.normalize(self.array)
end

Vector.Vec4.prototype.distanceTo = function(self, v)
   return honey.cglm.vec4.distance(self.array, v.array)
end

Vector.Vec4.prototype.lerp = function(self, v, s, dest)
   local result
   if dest == nil then
      result = Vector.Vec4.new()
   else
      result = dest
   end

   honey.cglm.vec4.lerp(self.array, v.array, s, result.array)
   return result
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vector.Vec4.mt = {}
Vector.Vec4.mt.__index = Vector.Vec4.prototype
Vector.Vec4.mt.__tostring = function(vec4)
   local str = 'vec4('..
      tostring(vec4:at(0))..', '..
      tostring(vec4:at(1))..', '..
      tostring(vec4:at(2))..', '..
      tostring(vec4:at(3))..')'
   return str
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vector.Vec4.new = function(tbl)
   local vec4 = {}
   vec4.array = honey.cglm.new_array_zero(4)
   setmetatable(vec4, Vector.Vec4.mt)

   if tbl == nil then return vec4 end

   for i=0,3 do
      vec4:setAt(i, tbl[i+1])
   end

   return vec4
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

return Vector

   
   


