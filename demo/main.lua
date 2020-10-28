local Vec3, Vec4 = require('Vector')()
local Mat3, Mat4 = require('Matrix')()
local FPSCamera = require('FPSCamera')

local model = Mat4.new()
honey.cglm.mat4.identity(model)
honey.cglm.affine.rotate(model, Vec3.ZERO, Vec3.X_UNIT, math.pi/4)

honey.input.key.bind(honey.input.key.escape, honey.exit)

local vertex_shader = [[
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * vec4(position.xyz, 1);
} ]]
local fragment_shader = [[
#version 330 core
uniform vec4 base_color;

out vec4 color;
void main() { color = base_color; } ]]

local shader = honey.shader.new(vertex_shader, fragment_shader)
local plane = honey.primitives.cube(10,10,10)

local color1 = Vec4.new{1,0,0,1}
local color2 = Vec4.new{0,0,1,1}
local color = honey.cglm.new_array_zero(4)

local total_time = 0

function honey.update(dt)
    total_time = total_time + dt
    honey.cglm.vec4.lerp(color1, color2, 0.5*(math.sin(math.pi*total_time)+1), color)
end

function honey.draw()
    FPSCamera:update()
    honey.shader.set_mat4(shader, 'model', model)
    honey.shader.set_mat4(shader, 'view', FPSCamera.view)
    honey.shader.set_mat4(shader, 'projection', FPSCamera.projection)
    honey.shader.set_vec4(shader, "base_color", color)
    honey.mesh.draw(plane, shader)
end
