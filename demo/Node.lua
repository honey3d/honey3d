local Node = {}

Node.prototype = {}

Node.prototype.updateTransform = function(self)
   self.transform:eye()

   self.transform:translate(self.position)

   self.transform:rotateZ(self.rotation:get(2))
   self.transform:rotateY(self.rotation:get(1))
   self.transform:rotateX(self.rotation:get(0))

   self.transform:scalev(self.scale)

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

local rotationAxes = { x=0, y=1, z=2 }

function Node.prototype.rotate(self, axis, angle)
   local index = rotationAxes[axis]
   local oldAngle = self.rotation:get(index)
   self.rotation:set(index, oldAngle + angle)
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Node.mt = {}
Node.mt.__index = Node.prototype

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Node.new = function(parent, position, rotation, scale)
   local node = {}

   setmetatable(node, Node.mt)

   node.parent = parent

   if not position then node.position = honey.glm.vec3{0,0,0}
   else node.position = position end
   
   if not rotation then node.rotation = honey.glm.vec3{0,0,0}
   else node.rotation = rotation end

   if not scale then node.scale = honey.glm.vec3{1,1,1}
   else node.scale = scale end

   node.children = {}

   if parent ~= nil then
      local index = #parent.children
      parent.children[index + 1] = node
   end
   
   node.transform = honey.glm.mat4()
   node.transform:eye()
   node:updateTransform()

   return node
end

return Node
