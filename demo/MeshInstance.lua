local Node = require('Node')

local MeshInstance = {}

MeshInstance.prototype = {}
setmetatable(MeshInstance.prototype, { __index = Node.prototype})

MeshInstance.prototype.draw = function(self, shader, camera)
   honey.texture.use(self.texture, 0)
   honey.shader.set_mat4(shader, 'model', self.transform.array)
   honey.shader.set_mat4(shader, 'view', camera.view.array)
   honey.shader.set_mat4(shader, 'projection', camera.view.array)
   honey.mesh.draw(self.mesh, shader)
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MeshInstance.mt = {}
MeshInstance.mt.__index = MeshInstance.prototype

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MeshInstance.new = function(parent, position, rotation, scale, mesh)
   local meshinstance = Node.new(parent, postion, rotation, scale)
   setmetatable(meshinstance, MeshInstance.mt)

   meshinstance.mesh = mesh

   return meshinstance
end
