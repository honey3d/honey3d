local Shader = {}

Shader.prototype = {}

Shader.prototype.setInteger = function(self, uniform, integer)
   honey.shader.set_int(self.program, uniform, integer)
end

Shader.prototype.setFloat = function(self, uniform, float)
   honey.shader.set_float(self.program, uniform, float)
end

Shader.prototype.setVec3 = function(self, uniform, vector)
   honey.shader.set_vec3(self.program, uniform, vector.array)
end

Shader.prototype.setVec4 = function(self, uniform, vector)
   honey.shader.set_vec4(self.program, uniform, vector.array)
end

Shader.prototype.setMat3 = function(self, uniform, matrix)
   honey.shader.set_mat3(self.program, uniform, matrix.array)
end

Shader.prototype.setMat4 = function(self, uniform, matrix)
   honey.shader.set_mat4(self.program, uniform, matrix.array)
end

Shader.prototype.drawMesh = function(self, mesh)
   honey.mesh.draw(mesh.mesh, self.program)
end

Shader.prototype.delete = function(self)
   honey.shader.delete(self.program)
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Shader.mt = {}
Shader.mt.__index = Shader.prototype

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Shader.new = function(vertexCode, fragmentCode)
   local shader = {}
   shader.program = honey.shader.new(vertexCode, fragmentCode)

   setmetatable(shader, Shader.mt)

   return shader
end

return Shader
