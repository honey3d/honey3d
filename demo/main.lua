local Node = require('Node')
local FPSCamera = require('FPSCamera')
local SpatialShader = require('SpatialShader')
local Primitives = require('Primitives')
-- local ScreenQuad = require('ScreenQuad')
local MeshInstance = require('MeshInstance')
FPSCamera.movement_speed = 5

honey.input.key.bind(honey.input.key.escape, honey.exit)

local buffer = false
honey.input.key.bind(honey.input.key.f,
                     function(action)
                        if action == 1 then
                           buffer = not buffer
                        end
end)
                     
local tex = honey.texture.load('lowres.png',
                               {minFilter='nearest', magFilter='nearest'})

local cairo = honey.cairo()
cairo:setColor(1, 1, 1)
cairo:moveTo(1024,0)
cairo:lineTo(0,1024)
cairo:stroke()

cairo:setColor(1, 0, 1, 0.2)
cairo:moveTo(0,0)
cairo:lineTo(1024,1024)
cairo:stroke()

cairo:updateTexture()

local sceneRoot = Node.new()

local shader = SpatialShader.new(cairo:getTexture())
local lightDirection = honey.glm.vec3{1,1,1}
lightDirection:normalize()
shader:setVec3('directional_lights[0].direction', lightDirection)
shader:setVec3('directional_lights[0].color', honey.glm.vec3{0,1,0})
local meshes = honey.loadMesh('Suzanne.obj')
local suzanne = MeshInstance.new(sceneRoot,
                                 honey.glm.vec3{0,0,3},
                                 honey.glm.vec3{0,math.pi,0},
                                 honey.glm.vec3{0.5,1,0.5},
                                 meshes[1],
                                 shader)
print(suzanne.mesh)
--local plane = MeshInstance.new(suzanne,
--                               honey.glm.vec3{1,0,0},
--                               honey.glm.vec3{0,0,0},
--                               honey.glm.vec3{1,1,1},
--                               Primitives.plane(4,4),
--                               shader)

MeshInstance.new(sceneRoot,
                 honey.glm.vec3{0,0,3},
                 honey.glm.vec3{0,0,0},
                 honey.glm.vec3{1,1,1},
                 Primitives.plane(4,4),
                 shader)

MeshInstance.new(sceneRoot,
                 honey.glm.vec3{4,0,3},
                 honey.glm.vec3{0,math.pi,0},
                 honey.glm.vec3{1,1,1},
                 Primitives.plane(4,4),
                 shader)

suzanne.update = function(self, dt)
   self:rotate('y', dt)
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
      print(cairo)
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
      honey.clear_color(honey.glm.vec4(), true, true, false)
      honey.enable_depth_test(true)
      draw_suzanne()
      
      honey.set_framebuffer(0)
      honey.set_viewport_size(640, 480)
      honey.enable_depth_test(false)
      honey.clear_color(honey.glm.vec4{0,0,1,1}, true, false, false)
      ScreenQuad:draw()
   else
      honey.clear_color(honey.glm.vec4{1,1,0,1}, true, true, false)
      honey.set_viewport_size(640, 480)
      honey.enable_depth_test(true)
      draw_suzanne()
   end
end
