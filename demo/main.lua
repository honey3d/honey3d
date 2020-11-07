local Vector = require('Vector')
local Matrix = require('Matrix')
local FPSCamera = require('FPSCamera')
local ScreenQuad = require('ScreenQuad')
local MeshInstance = require('MeshInstance')
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
local suzanne = MeshInstance.new(nil,
                                 Vector.Vec3.new{0,0,-3},
                                 Vector.Vec3.new{0,math.pi,0},
                                 Vector.Vec3.new{1,1,1},
                                 honey.mesh.load('Suzanne.obj')[1])
local plane = MeshInstance.new(suzanne,
                               Vector.Vec3.new{-2,5,0},
                               Vector.Vec3.new{0,0,0},
                               Vector.Vec3.new{1,1,1},
                               honey.primitives.plane(4,4))
suzanne.update = function(self, dt)
   local movement = Vector.Vec3.new()
   movement:add(Vector.Vec3.X_UNIT, movement)
   movement:muls(dt, movement)
   self:translate(movement)
   self:updateTransform()
end

local total_frames = 0
local total_time = 0

honey.window.set_size(640, 480)

function honey.update(dt)
   total_time = total_time + dt
   FPSCamera:update(dt)
   suzanne:update(dt)
   if total_time > 1 then
      print('FPS: '..tostring(total_frames/total_time))
      total_time = 0
      total_frames = 0
   end
end

function draw_suzanne()
   honey.texture.use(tex, 0)
   suzanne:draw(shader, FPSCamera)
   plane:draw(shader, FPSCamera)
end

function honey.draw()
   total_frames = total_frames + 1

   if buffer then
      honey.set_framebuffer(ScreenQuad.fb)
      honey.set_viewport_size(480,640)
      honey.clear_color(Vector.Vec4.new().array, true, true, false)
      honey.enable_depth_test(true)
      draw_suzanne()
      
      honey.set_framebuffer(0)
      honey.set_viewport_size(640, 480)
      honey.enable_depth_test(false)
      honey.clear_color(Vector.Vec4.new{0,0,1,1}.array, true, false, false)
      ScreenQuad:draw()
   else
      honey.clear_color(Vector.Vec4.new{1,1,0,1}.array, true, true, false)
      honey.set_viewport_size(640, 480)
      honey.enable_depth_test(true)
      draw_suzanne()
   end
end
