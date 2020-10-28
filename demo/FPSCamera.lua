local Vec3, Vec4 = require('Vector')()
local Mat3, Mat4 = require('Matrix')()

local Basis = function(M)
    local m = Mat3.new()
    honey.cglm.mat4.pick3(M, m)

    local x0 = honey.cglm.get_value(m, Mat3.index(1,1))
    local x1 = honey.cglm.get_value(m, Mat3.index(2,1))
    local x2 = honey.cglm.get_value(m, Mat3.index(3,1))

    local y0 = honey.cglm.get_value(m, Mat3.index(1,2))
    local y1 = honey.cglm.get_value(m, Mat3.index(2,2))
    local y2 = honey.cglm.get_value(m, Mat3.index(3,2))

    local z0 = honey.cglm.get_value(m, Mat3.index(1,3))
    local z1 = honey.cglm.get_value(m, Mat3.index(2,3))
    local z2 = honey.cglm.get_value(m, Mat3.index(3,3))
    
    local b = {}
    b.x = Vec3.new{x0, x1, x2}
    b.y = Vec3.new{y0, y1, y2}
    b.z = Vec3.new{z0, z1, z2}

    return b
end

local camera = {}

camera.pitch = 0
camera.yaw = 0

camera.sensitivity = 0.1

camera.movement_speed = 1

camera.position = Vec3.new{0,0,-1}

camera.view = Mat4.new()
honey.cglm.mat4.identity(camera.view)

camera.basis = Basis(camera.view)

camera.projection = Mat4.new()
honey.cglm.camera.perspective(
    camera.projection,
    math.rad(90),
    640/480,
    0.1,
    8192)

function camera:update()
    local M = Mat4.new()
    honey.cglm.mat4.identity(M)
    honey.cglm.affine.rotate(M, Vec3.ZERO, self.basis.x, math.rad(self.pitch))
    honey.cglm.affine.rotate(M, Vec3.ZERO, Vec3.Y_UNIT, math.rad(self.yaw))
    self.basis = Basis(M)

    movement = Vec3.new()
    if honey.input.key.is_down(honey.input.key.w) then honey.cglm.vec3.add(movement, self.basis.z, movement) end
    if honey.input.key.is_down(honey.input.key.a) then honey.cglm.vec3.add(movement, self.basis.x, movement) end
    if honey.input.key.is_down(honey.input.key.s) then honey.cglm.vec3.sub(movement, self.basis.z, movement) end
    if honey.input.key.is_down(honey.input.key.d) then honey.cglm.vec3.sub(movement, self.basis.x, movement) end
    
    honey.cglm.set_value(movement, 1, 0)
    honey.cglm.vec3.normalize(movement)
    honey.cglm.vec3.muls(self.movement_speed, movement, movement)
    honey.cglm.vec3.add(self.position, movement, self.position)
    
    honey.cglm.camera.look(self.position, self.basis.z, Vec3.Y_UNIT, self.view)
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
