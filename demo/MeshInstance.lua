local Node = require('Node')

local MeshInstance = {}

MeshInstance.prototype = {}
setmetatable(MeshInstance.prototype, { __index = Node.prototype})

MeshInstance.prototype.draw = function(self, camera, shader)
   local shader = shader or self.shader
   
   honey.shader.set_mat4(shader, 'model', self.transform.array)
   honey.shader.set_mat4(shader, 'view', camera.view.array)
   honey.shader.set_mat4(shader, 'projection', camera.projection.array)
   honey.mesh.draw(self.mesh, shader)

   for _, child in ipairs(self.children) do
      child:draw(camera)
   end
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MeshInstance.mt = {}
MeshInstance.mt.__index = MeshInstance.prototype

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MeshInstance.new = function(parent, position, rotation, scale, mesh, shader)
   local meshinstance = Node.new(parent, position, rotation, scale)
   meshinstance.mesh = mesh
   meshinstance.shader = shader

   setmetatable(meshinstance, MeshInstance.mt)

   return meshinstance
end

return MeshInstance
