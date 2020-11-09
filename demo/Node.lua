local Vector = require('Vector')
local Matrix = require('Matrix')

local Node = {}

Node.prototype = {}

Node.prototype.updateTransform = function(self)
   honey.cglm.mat4.identity(self.transform.array)

   self.transform:translate(self.position)

   self.transform:rotate(Vector.Vec3.ZERO, Vector.Vec3.Z_UNIT, self.rotation:at(2))
   self.transform:rotate(Vector.Vec3.ZERO, Vector.Vec3.Y_UNIT, self.rotation:at(1))
   self.transform:rotate(Vector.Vec3.ZERO, Vector.Vec3.X_UNIT, self.rotation:at(0))

   self.transform:scale(self.scale)

   if self.parent ~= nil then
      self.parent.transform:mul(self.transform, self.transform)
   end

   for _, child in ipairs(self.children) do
      child:updateTransform()
   end
end

Node.prototype.updateCascade = function(self, dt)
    if self.update then
        self:update(dt)
    end
    self:updateTransform()
    for _, child in ipairs(self.children) do
        child:updateCascade(dt)
    end
end

Node.prototype.drawCascade = function(self, camera, shader)
    if self.draw then
        self:draw(camera, shader)
    end
    
   -- do not draw base nodes, but recursively draw children.
   for _, child in ipairs(self.children) do
      child:drawCascade(camera, shader)
   end
end

Node.prototype.translate = function(self, translation)
   self.position:add(translation, self.position)
end

Node.prototype.pitch = function(self, angle)
   self.rotation:setAt(0, self.rotation:at(0) + angle)
end

Node.prototype.yaw = function(self, angle)
   self.rotation:setAt(1, self.rotation:at(1) + angle)
end

Node.prototype.roll = function(self, angle)
   self.rotation:setAt(2, self.rotation:at(2) + angle)
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
