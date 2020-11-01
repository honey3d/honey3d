local Vector = require('Vector')
local Matrix = require('Matrix')
local Node = require('Node')

local Camera = {}

Camera.prototype = {}
setmetatable(Camera.prototype, { __index = Node.prototype })

Camera.prototype.updateView = function(self)
   self.basis = self.transform:basis()
   Matrix.Mat4.look(self.position, self.basis.z, self.basis.y, self.view)
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Camera.mt = {}
Camera.mt.__index = Camera.prototype

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Camera.new = function(parent, position, rotation, scale, fov, aspect, near, far)
   local camera = Node.new(parent, position, rotation, scale)
   setmetatable(camera, Camera.mt)

   camera.view = Matrix.Mat4.new()
   camera:updateView()
   camera.projection = Matrix.Mat4.perspective(fov, aspect, near, far)

   return camera
end

return Camera
   
