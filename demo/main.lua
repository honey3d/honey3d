local Vector = require('Vector')
local Matrix = require('Matrix')
local FPSCamera = require('FPSCamera')
local Node = require('Node')
local SpatialShader = require('SpatialShader')
local ScreenQuad = require('ScreenQuad')
local MeshInstance = require('MeshInstance')
FPSCamera.movement_speed = 5

honey.input.key.bind(honey.input.key.escape, honey.exit)

local buffer = false
honey.input.key.bind(honey.input.key.f, function(action) if action == 1 then buffer = not buffer end end)

local tex = honey.texture.new()
honey.texture.load(tex, 'checkerboard.png', false)

local sceneRoot = Node.new(nil,
                           Vector.Vec3.new(),
                           Vector.Vec3.new(),
                           Vector.Vec3.new{1,1,1})

local shader = SpatialShader.new(tex)
local suzanne = MeshInstance.new(sceneRoot,
                                 Vector.Vec3.new{0,0,-3},
                                 Vector.Vec3.new{0,math.pi,0},
                                 Vector.Vec3.new{0.5,1,0.5},
                                 honey.mesh.load('Suzanne.obj')[1],
                                 shader)
local plane = MeshInstance.new(suzanne,
                               Vector.Vec3.new{1,0,0},
                               Vector.Vec3.new{0,0,0},
                               Vector.Vec3.new{1,1,1},
                               honey.primitives.plane(4,4),
                               shader)
local plane2 = MeshInstance.new(suzanne,
                                Vector.Vec3.new{5,0,0},
                                Vector.Vec3.new{0,math.pi,0},
                                Vector.Vec3.new{1,1,1},
                                honey.primitives.plane(4,4),
                                shader)

suzanne.update = function(self, dt)
   local angle = dt * math.pi
   self:yaw(angle)
end

local total_frames = 0
local total_time = 0

honey.window.set_size(640, 480)

function honey.update(dt)
   total_time = total_time + dt
   FPSCamera:update(dt)
   sceneRoot:updateCascade(dt)
   if total_time > 1 then
      print('FPS: '..tostring(total_frames/total_time))
      total_time = 0
      total_frames = 0
   end
end

function draw_suzanne()
   sceneRoot:drawCascade(FPSCamera)
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
