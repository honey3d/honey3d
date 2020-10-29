local Vector = require('Vector')
local Matrix = require('Matrix')

local camera = {}

camera.pitch = 0
camera.yaw = 0

camera.sensitivity = 0.1

camera.movement_speed = 1

camera.position = Vector.Vec3.new{0,0,-1}

camera.view = Matrix.Mat4.eye()
camera.basis = camera.view:basis()

camera.projection = Matrix.Mat4.perspective(math.rad(90),
					    640/480,
					    0.1,
					    8192)

function camera:update()
   local M = Matrix.Mat4.eye()
   M:rotate(Vector.Vec3.ZERO, self.basis.x, math.rad(self.pitch))
   M:rotate(Vector.Vec3.ZERO, Vector.Vec3.Y_UNIT, math.rad(self.yaw))
   self.basis = M:basis()

   movement = Vector.Vec3.new()
   if honey.input.key.is_down(honey.input.key.w) then
      movement:add(self.basis.z, movement)
   end
   if honey.input.key.is_down(honey.input.key.a) then
      movement:add(self.basis.x, movement)
   end
   if honey.input.key.is_down(honey.input.key.s) then
      movement:sub(self.basis.z, movement)
   end
   if honey.input.key.is_down(honey.input.key.d) then
      movement:sub(self.basis.x, movement)
   end
   
   movement:setAt(1, 0)
   movement:normalize()
   movement:muls(self.movement_speed, movement)
   self.position:add(movement, self.position)

   Matrix.Mat4.look(self.position, self.basis.z, Vector.Vec3.Y_UNIT, self.view)
end

camera.mouse_pos = {}
camera.mouse_pos.x = 0
camera.mouse_pos.y = 0

honey.input.mouse.bind_movement(
   function(xpos, ypos)
      local dx = xpos - camera.mouse_pos.x
      local dy = ypos - camera.mouse_pos.y

      camera.mouse_pos = { x=xpos, y=ypos }

      camera.pitch = camera.pitch + camera.sensitivity * dy
      camera.yaw = camera.yaw - camera.sensitivity * dx

      if camera.pitch > 89 then camera.pitch = 89 end
      if camera.pitch < -89 then camera.pitch = -89 end
   end
)

honey.input.mouse.set_mode(honey.input.mouse.mode.disabled)

return camera
