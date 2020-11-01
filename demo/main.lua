local Vector = require('Vector')
local Matrix = require('Matrix')
local FPSCamera = require('FPSCamera')
local ScreenQuad = require('ScreenQuad')
FPSCamera.movement_speed = 5

local model = Matrix.Mat4.eye()
model:rotate(Vector.Vec3.ZERO, Vector.Vec3.Y_UNIT, math.pi)
model:translate(Vector.Vec3.new{0,0,-2})
print(model)

honey.input.key.bind(honey.input.key.escape, honey.exit)

local buffer = false
honey.input.key.bind(honey.input.key.f, function(action) if action == 1 then buffer = not buffer end end)

local tex = honey.texture.new()
honey.texture.load(tex, 'checkerboard.png', false)

local vertex_shader = [[
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Position;
out vec3 Normal;
out vec2 UV;

void main()
{
  gl_Position = projection * view * model * vec4(position.xyz, 1);
  Position = gl_Position.xyz;
  Normal = normal;
  UV = uv;
} ]]
local fragment_shader = [[
#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;

uniform float time;
uniform sampler2D tex;

out vec4 color;

void main() { 
  //vec2 texture_coords = UV + (time * vec2(100,100));
  color = vec4(texture(tex, UV).xyz, 1); 
} ]]

local shader = honey.shader.new(vertex_shader, fragment_shader)
local suzanne = honey.mesh.load('Suzanne.obj')[1]
local plane = honey.primitives.plane(4,4)

local color1 = Vector.Vec4.new{1,0,0,1}
local color2 = Vector.Vec4.new{0,0,1,1}
local color = Vector.Vec4.new()

local total_frames = 0
local total_time = 0

function honey.update(dt)
   total_time = total_time + dt
   FPSCamera:update(dt)
   if total_time > 1 then
      print('FPS: '..tostring(total_frames/total_time))
      total_time = 0
      total_frames = 0
   end
end

function draw_suzanne()
   honey.texture.use(tex, 0)
   honey.shader.set_mat4(shader, 'model', model.array)
   honey.shader.set_mat4(shader, 'view', FPSCamera.view.array)
   honey.shader.set_mat4(shader, 'projection', FPSCamera.projection.array)
   honey.shader.set_float(shader, 'time', total_time)
   honey.mesh.draw(suzanne, shader)
   honey.mesh.draw(plane, shader)
end

function honey.draw()
   total_frames = total_frames + 1

   if buffer then
      honey.set_framebuffer(ScreenQuad.fb)
      honey.enable_depth_test(true)
      honey.clear_color(Vector.Vec4.new().array, true, true, false)
      draw_suzanne()
      
      honey.set_framebuffer(0)
      honey.enable_depth_test(true)
      honey.clear_color(Vector.Vec4.new{0,0,1,1}.array, true, true, false)
      ScreenQuad:draw()
   else
      honey.clear_color(Vector.Vec4.new{1,1,0,1}.array, true, true, false)
      honey.enable_depth_test(true)
      draw_suzanne()
   end
end
