local Camera = require('Camera')

local camera = Camera.new(nil,
                          honey.glm.vec3(),
                          honey.glm.vec3(),
                          honey.glm.vec3{1,1,1},
                          math.rad(90), 640/480, 0.1, 1000)

camera.pitch = 0
camera.yaw = 0

camera.sensitivity = 0.1

camera.movement_speed = 1

function camera:update(dt)
   movement = honey.glm.vec3()
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

   movement:set(1, 0)
   movement:normalize()

   if honey.input.key.is_down(honey.input.key.left_shift) then
      movement:add(honey.glm.UNIT_Y, movement)
   end
   if honey.input.key.is_down(honey.input.key.left_control) then
      movement:sub(honey.glm.UNIT_Y, movement)
   end
   movement:muls(self.movement_speed*dt, movement)
   self:translate(movement)
   
   self:updateTransform()
   self:updateView()
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

      if camera.pitch > 89.9 then camera.pitch = 89.9 end
      if camera.pitch < -89.9 then camera.pitch = -89.9 end

      camera.rotation:set(0, math.rad(camera.pitch))
      camera.rotation:set(1, math.rad(camera.yaw))
   end
)

honey.input.mouse.set_mode(honey.input.mouse.mode.captured)

return camera
