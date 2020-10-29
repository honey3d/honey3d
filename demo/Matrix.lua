local Vector = require('Vector')

local Matrix = {}

Matrix.Mat3 = {}

Matrix.Mat3.prototype = {}

Matrix.Mat3.prototype.at = function(self, i, j)
   return honey.cglm.get_value(self.array, (i-1) + 3*(j-1))
end

Matrix.Mat3.prototype.setAt = function(self, i, j, value)
   honey.cglm.set_value(self.array, (i-1) + 3*(j-1), value)
end

Matrix.Mat3.prototype.clone = function(self)
   local clone = honey.cglm.new_array_zero(9)
   clone.array = honey.cglm.copy_array(self.array, 9)
   return clone
end

Matrix.Mat3.prototype.mul = function(self, M, dest)
   local result
   if dest == nil then
      result = Matrix.Mat3.new()
   else
      result = dest
   end

   honey.cglm.mat3.mul(self.array, M.array, result)
   return result
end

Matrix.Mat3.prototype.muls = function(self, s, dest)
   local result
   if dest == nil then
      result = Matrix.Mat3.new()
   else
      result = dest
   end

   honey.cglm.mat3.muls(s, self.array, result)
   return result
end

Matrix.Mat3.prototype.mulv = function(self, v, dest)
   local result
   if dest == nil then
      result = Matrix.Vec3.new()
   else
      result = dest
   end

   honey.cglm.mat3.mulv(self.array, v.array, result)
   return result
end
 
Matrix.Mat3.prototype.T = function(self, auto)
   auto = auto or false   
   if auto then
      honey.cglm.mat3.trans(self.array)
      return
   end

   local M = self.clone()
      
   honey.cglm.mat3.trans(M.array)
   return M
end

Matrix.Mat3.prototype.det = function(self)
   return honey.cglm.mat3.det(self.array)
end

Matrix.Mat3.prototype.trace = function(self)
   return honey.cglm.mat3.trace(self.array)
end

Matrix.Mat3.prototype.inv = function(self, dest)
   local result
   if dest == nil then
      result = Matrix.Mat3.new()
   else
      result = dest
   end

   honey.cglm.mat3.inv(self.array, result.array)
   return result
end

Matrix.Mat3.prototype.basis = function(self)
   local x0 = self:at(1,1)
   local x1 = self:at(2,1)
   local x2 = self:at(3,1)

   local y0 = self:at(1,2)
   local y1 = self:at(2,2)
   local y2 = self:at(3,2)

   local z0 = self:at(1,3)
   local z1 = self:at(2,3)
   local z2 = self:at(3,3)
   
   local b = {}
   b.x = Vector.Vec3.new{x0, x1, x2}
   b.y = Vector.Vec3.new{y0, y1, y2}
   b.z = Vector.Vec3.new{z0, z1, z2}

   return b
end
   
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Matrix.Mat3.mt = {}

Matrix.Mat3.mt.__index = Matrix.Mat3.prototype
Matrix.Mat3.mt.__tostring = function(mat3)
   local line1 = 'mat3('..
      tostring(mat3:at(1,1))..', '..
      tostring(mat3:at(1,2))..', '..
      tostring(mat3:at(1,3))..', \n'
   local line2 = '    '..
      tostring(mat3:at(2,1))..', '..
      tostring(mat3:at(2,2))..', '..
      tostring(mat3:at(2,3))..', \n'
   local line3 = '    '..
      tostring(mat3:at(3,1))..', '..
      tostring(mat3:at(3,2))..', '..
      tostring(mat3:at(3,3))..')'
   return line1..line2..line3
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Matrix.Mat3.new = function(tbl)
   local mat3 = {}
   mat3.array = honey.cglm.new_array_zero(9)
   setmetatable(mat3, Matrix.Mat3.mt)

   if tbl == nil then return mat3 end
   
   for i = 1,3 do
      for j = 1,3 do
	 mat3:setAt(i,j, tbl[3*(i-1) + j])
      end
   end

    return mat3
end

Matrix.Mat3.eye = function()
   local eye3 = Matrix.Mat3.new()
   honey.cglm.mat3.identity(eye3.array)
   return eye3
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
--
-- Mat4
--
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Matrix.Mat4 = {}

Matrix.Mat4.prototype = {}

Matrix.Mat4.prototype.at = function(self, i, j)
   return honey.cglm.get_value(self.array, (i-1) + 4*(j-1))
end

Matrix.Mat4.prototype.setAt = function(self, i, j, value)
   honey.cglm.set_value(self.array, (i-1) + 4*(j-1), value)
end

Matrix.Mat4.prototype.clone = function(self)
   local clone = honey.cglm.new_array_zero(16)
   clone.array = honey.cglm.copy_array(self.array, 16)
   return clone
end

Matrix.Mat4.prototype.pick3 = function(self, dest)
   local result
   if dest == nil then
      result = Matrix.Mat3.new()
   else
      result = dest
   end

   honey.cglm.mat4.pick3(self.array, result.array)
   return result
end

Matrix.Mat4.prototype.mul = function(self, M, dest)
   local result
   if dest == nil then
      result = Matrix.Mat4.new()
   else
      result = dest
   end

   honey.cglm.mat4.mul(self.array, M.array, result)
   return result
end

Matrix.Mat4.prototype.muls = function(self, s, dest)
   local result
   if dest == nil then
      result = Matrix.Mat4.new()
   else
      result = dest
   end

   honey.cglm.mat4.muls(s, self.array, result)
   return result
end

Matrix.Mat4.prototype.mulv = function(self, v, dest)
   local result
   if dest == nil then
      result = Matrix.Vec4.new()
   else
      result = dest
   end

   honey.cglm.mat4.mulv(self.array, v.array, result)
   return result
end
 
Matrix.Mat4.prototype.T = function(self, auto)
   auto = auto or false   
   if auto then
      honey.cglm.mat4.trans(self.array)
      return
   end

   local M = self.clone()
      
   honey.cglm.mat4.trans(M.array)
   return M
end

Matrix.Mat4.prototype.det = function(self)
   return honey.cglm.mat4.det(self.array)
end

Matrix.Mat4.prototype.trace = function(self)
   return honey.cglm.mat4.trace(self.array)
end

Matrix.Mat4.prototype.inv = function(self, dest)
   local result
   if dest == nil then
      result = Matrix.Mat4.new()
   else
      result = dest
   end

   honey.cglm.mat4.inv(self.array, result.array)
   return result
end

Matrix.Mat4.prototype.fastInv = function(self, dest)
   local result
   if dest == nil then
      result = Matrix.Mat4.new()
   else
      result = dest
   end

   honey.cglm.mat4.inv_fast(self.array, result.array)
   return result
end

Matrix.Mat4.prototype.basis = function(self)
   local M = self:pick3()

   return M:basis()
end

Matrix.Mat4.prototype.rotate = function(self, center, axis, angle)
   honey.cglm.affine.rotate(self.array, center.array, axis.array, angle)
end

Matrix.Mat4.prototype.translate = function(self, v)
   honey.cglm.affine.translate(self.array, v.array)
end

Matrix.Mat4.prototype.scale = function(self, v)
   honey.cglm.affine.scale(self.array, v.array)
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Matrix.Mat4.mt = {}

Matrix.Mat4.mt.__index = Matrix.Mat4.prototype
Matrix.Mat4.mt.__tostring = function(mat4)
   local line1 = 'mat4('..
      tostring(mat4:at(1,1))..', '..
      tostring(mat4:at(1,2))..', '..
      tostring(mat4:at(1,3))..', '..
      tostring(mat4:at(1,4))..', \n'
   local line2 = '    '..
      tostring(mat4:at(2,1))..', '..
      tostring(mat4:at(2,2))..', '..
      tostring(mat4:at(2,3))..', '..
      tostring(mat4:at(2,4))..', \n'
   local line3 = '    '..
      tostring(mat4:at(3,1))..', '..
      tostring(mat4:at(3,2))..', '..
      tostring(mat4:at(3,3))..', '..
      tostring(mat4:at(3,4))..')'
   local line4 = '    '..
      tostring(mat4:at(4,1))..', '..
      tostring(mat4:at(4,2))..', '..
      tostring(mat4:at(4,3))..', '..
      tostring(mat4:at(4,4))..')'
   return line1..line2..line4
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Matrix.Mat4.new = function(tbl)
   local mat4 = {}
   mat4.array = honey.cglm.new_array_zero(16)
   setmetatable(mat4, Matrix.Mat4.mt)

   if tbl == nil then return mat4 end
   
   for i = 1,4 do
      for j = 1,4 do
	 mat4:setAt(i,j, tbl[4*(i-1) + j])
      end
   end

    return mat4
end

Matrix.Mat4.eye = function()
   local eye4 = Matrix.Mat4.new()
   honey.cglm.mat4.identity(eye4.array)
   return eye4
end

Matrix.Mat4.perspective = function(fov, aspectRatio, near, far)
   local M = Matrix.Mat4.new()
   honey.cglm.camera.perspective(M.array, fov, aspectRatio, near, far)
   return M
end

Matrix.Mat4.orthographic = function(a, b)
   local M = Matrix.Mat4.new()
   honey.cglm.camera.orthographic(M.array, a.array, b.array)
   return M
end

Matrix.Mat4.look = function(position, direction, up, dest)
   local result
   if dest == nil then
      result = Matrix.Mat4.new()
   else
      result = dest
   end

   honey.cglm.camera.look(position.array,
			  direction.array,
			  up.array,
			  dest.array)
   return dest
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

return Matrix
