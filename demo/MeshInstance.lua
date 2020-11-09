local Node = require('Node')

local MeshInstance = {}

MeshInstance.prototype = {}
setmetatable(MeshInstance.prototype, { __index = Node.prototype})

MeshInstance.prototype.draw = function(self, camera, shader)
   local shader = shader or self.shader
   
   shader:setCamera(camera)
   shader:drawMesh(self)
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
