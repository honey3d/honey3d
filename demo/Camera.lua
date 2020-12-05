local Node = require('Node')

local Camera = {}

Camera.prototype = {}
setmetatable(Camera.prototype, { __index = Node.prototype })

Camera.prototype.updateView = function(self)
   self.basis = self.transform:basis()
   self.view:look(self.position, self.basis.z, self.basis.y)
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Camera.mt = {}
Camera.mt.__index = Camera.prototype

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Camera.new = function(parent, position, rotation, scale, fov, aspect, near, far)
   local camera = Node.new(parent, position, rotation, scale)
   setmetatable(camera, Camera.mt)

   camera.view = honey.glm.mat4()
   camera:updateView()
   camera.projection = honey.glm.mat4()
   camera.projection:perspective(fov, aspect, near, far)

   return camera
end

return Camera
   
