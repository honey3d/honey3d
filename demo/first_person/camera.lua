local Camera = {}
local G = _G
local honey = honey
local math = math
local glm = honey.glm
setmetatable(Camera, {__index=_G})
setfenv(1, Camera)

local X = glm.makeVector(1, 0, 0)
local Y = glm.makeVector(0, 1, 0)
local Z = glm.makeVector(0, 0, 1)


--===== constructor =====--

function constructor(_, fov, ratio, near, far)
	local self = {}
	G.setmetatable(self, {__index=Camera})

	self.projection = glm.mat4()
	self.fov = fov
	self.near = near
	self.far = far
	glm.perspective(fov, ratio, near, far, self.projection)

	self.position = glm.vec3()
	self.forward = glm.vec3()
	self.up = Y
	self.right = glm.vec3()

	self.view = glm.mat4()
	glm.mat4_identity(self.view)

	return self
end
setmetatable(Camera, {__call=constructor})


--===== methods =====--

function translate(self, translation)
	local v = glm.vec3()
	glm.vec3_scale(self.forward, glm.vec3_get(translation, 0), v)
	glm.vec3_add(self.position, v, self.position)

	glm.vec3_scale(self.right, glm.vec3_get(translation, 2), v)
	glm.vec3_add(self.position, v, self.position)
end


function setAngles(self, yaw, pitch)
	local yawr = math.rad(yaw)
	local pitchr = math.rad(pitch)

	local x = math.cos(yawr) * math.cos(pitchr)
	local y = math.sin(pitchr)
	local z = math.sin(yawr) * math.cos(pitchr)

	glm.setVector(self.forward, x, y, z)
	glm.vec3_cross(self.forward, self.up, self.right)
	glm.vec3_normalize(self.forward)
	glm.vec3_normalize(self.right)

	G.print(yaw, pitch, glm.vec3_tostring(self.forward), glm.vec3_tostring(self.right))
end


function updateView(self)
	glm.look(self.position, self.forward, self.up, self.view)
end


function updateRatio(self, ratio)
	glm.perspective(self.fov, ratio, self.near, self.far, self.projection)
end


--===== fin =====--

return Camera
