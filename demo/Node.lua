local Vector = require('Vector')
local Matrix = require('Matrix')

local Node = {}

Node.prototype = {}
Node.prototype.updateTransform = function(self)
   honey.cglm.mat4.identity(self.transform.array)

   self.transform:scale(self.scale)

   self.transform:rotate(Vector.Vec3.ZERO, Vector.Vec3.Z_UNIT, self.rotation:at(2))
   self.transform:rotate(Vector.Vec3.ZERO, Vector.Vec3.Y_UNIT, self.rotation:at(1))
   self.transform:rotate(Vector.Vec3.ZERO, Vector.Vec3.X_UNIT, self.rotation:at(0))

   self.transform:translate(self.position)

   if parent ~= nil then
      self.transform:mul(self.parent.transform)
   end
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Node.mt = {}
Node.mt.__index = Node.prototype

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Node.new = function(parent, position, rotation, scale)
   local node = {}

   setmetatable(node, Node.mt)

   node.parent = parent

   node.position = position
   node.rotation = rotation
   node.scale = scale
   
   node.transform = Matrix.Mat4.eye()
   node:updateTransform()

   return node
end

return Node
