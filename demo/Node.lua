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

   if self.parent ~= nil then
      self.transform:mul(self.parent.transform, self.transform)
   end

   for _, child in ipairs(self.children) do
      child:updateTransform()
   end
end

Node.prototype.translate = function(self, translation)
   self.position:add(translation, self.position)
end

Node.prototype.pitch = function(self, angle)
   self.rotation:setAt(0, angle)
end

Node.prototype.yaw = function(self, angle)
   self.rotation:setAt(1, angle)
end

Node.prototype.roll = function(self, angle)
   self.rotation:setAt(2, angle)
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

   node.children = {}

   if parent ~= nil then
      local index = #parent.children
      parent.children[index + 1] = node
   end
   
   node.transform = Matrix.Mat4.eye()
   node:updateTransform()

   return node
end

return Node
