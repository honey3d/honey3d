local Vector = require('Vector')
local Matrix = require('Matrix')
local FPSCamera = require('FPSCamera')

local model = Matrix.Mat4.eye()

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
local plane = honey.mesh.load('Suzanne.obj')[1]

local color1 = Vector.Vec4.new{1,0,0,1}
local color2 = Vector.Vec4.new{0,0,1,1}
local color = Vector.Vec4.new()

local total_time = 0

function honey.update(dt)
   total_time = total_time + dt
   color1:lerp(color2, 0.5*(math.sin(math.pi*total_time)+1), color)
   FPSCamera:update(dt)
end

function honey.draw()
   
   honey.shader.set_mat4(shader, 'model', model.array)
   honey.shader.set_mat4(shader, 'view', FPSCamera.view.array)
   honey.shader.set_mat4(shader, 'projection', FPSCamera.projection.array)
   honey.shader.set_vec4(shader, "base_color", color.array)
   honey.mesh.draw(plane, shader)
end
