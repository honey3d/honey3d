require 'common'

local window = honey.window
local glm = honey.glm

function makeVector(x, y, z)
	local vec = honey.glm.vec3()
	honey.glm.vec3_set(vec, 0, x)
	honey.glm.vec3_set(vec, 1, y)
	honey.glm.vec3_set(vec, 2, z) return vec
end

function printVector(vec)
	local x = honey.glm.vec3_get(vec, 0)
	local y = honey.glm.vec3_get(vec, 1)
	local z = honey.glm.vec3_get(vec, 2)
	print(string.format('[%0.2f, %0.2f, %0.2f]', x, y, z))
end

function pressed(key)
	local win = honey.window.win
	return window.getKey(win, key) == window.PRESS
end

local Shader = require 'shader'
local Mesh = require 'mesh'
local Camera = require 'camera'
local Texture = require 'texture'


local heightmap, camera, shader, texture

function honey.init()
	heightmap = Mesh.Load('heightmap.dae')
	glm.rotate(heightmap.transform, math.rad(90), glm.makeVector(1, 0, 0))
	camera = Camera(math.rad(45), 640/480, 0.1, 1000)
	shader = Shader.Load('height.vs', 'height.fs')
	texture = Texture.Load('grass3_by_RPG.png')

	shader:SetTexture('grass', texture)

	window.setInputMode(window.win, window.CURSOR, window.CURSOR_DISABLED)
end

function honey.windowSizeCallback(w, h)
	print('hi')
	honey.gl.Viewport(0, 0, w, h)
	camera:updateRatio(w/h)
end


local mouse = { x=0, y=0, pitch=0, yaw=0 }
local translation = honey.glm.vec3()
function honey.update(dt)
	if pressed(window.KEY_ESCAPE) then
		window.setShouldClose(honey.window.win, true)
	end

	local mx, my = window.getCursorPos(honey.window.win)
	local delta_mx, delta_my = mx - mouse.x, my - mouse.y
	mouse.x = mx
	mouse.y = my
	mouse.yaw = mouse.yaw + delta_mx 
	mouse.pitch = mouse.pitch - delta_my
	if mouse.pitch < -89.999 then mouse.pitch = -89.999 end
	if mouse.pitch > 89.999 then mouse.pitch = 89.999 end

	camera:setAngles(mouse.yaw, mouse.pitch)

	local cx, cy, cz = 0, 0, 0
	if pressed(window.KEY_W) then cx= 1 
	elseif pressed(window.KEY_S) then cx = -1 end
	if pressed(window.KEY_A) then cz = -1
	elseif pressed(window.KEY_D) then cz = 1 end

	glm.setVector(translation, cx, cy, cz)
	honey.glm.vec3_normalize(translation)
	honey.glm.vec3_scale(translation, dt, translation)
	camera:translate(translation)

	camera:updateView()
end

function honey.draw()
	shader:Use()
	shader:SetMatrix('view', camera.view)
	shader:SetMatrix('projection', camera.projection)
	shader:SetMatrix('model', heightmap.transform)

	heightmap:Draw()
end

honey.run()
