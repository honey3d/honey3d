local gl = honey.gl
local window = honey.window

local Shader = require 'shader'
local Mesh = require 'mesh'


--====== initialize opengl ======--

gl.Init()
window.setHint(window.hintType.contextVersionMajor, 3)
window.setHint(window.hintType.contextVersionMinor, 3)
window.setHint(window.hintType.openGlProfile, window.profileType.openGlCoreProfile)


--====== create window ======--

local w = window.create(640, 480, 'bouncing ball demo')
window.makeContextCurrent(w)
gl.InitGlad()
gl.Enable(gl.DEPTH_TEST)


local projection = honey.glm.mat4()
honey.glm.perspective(math.rad(45), 800/600, 0.1, 1000, projection)
window.setFramebufferSizeCallback(w, function(_, width, height)
	print(string.format("resize: (%d, %d)", width, height))
	gl.Viewport(0, 0, width, height)
	honey.glm.perspective(math.rad(45), width/height, 0.1, 1000, projection)
end)


--===== load mesh and shader =====--

local shader = Shader.Load('vertex.vs', 'fragment.fs')
local ball = Mesh.Load('ball.dae')

--===== set up ode =====--

local ode = honey.ode
ode.InitODE()
local world = ode.WorldCreate()
local space = ode.HashSpaceCreate()
ode.WorldSetGravity(world, 0, -10, 0)
ode.WorldSetCFM(world, 1e-5)
ode.CreatePlane(space, 0, 1, 0, 0)
local contactgroup = ode.JointGroupCreate()
local body = ode.BodyCreate(world)
local geom = ode.CreateSphere(space, 0.5)
local mass = ode.MassCreate()
ode.MassSetSphere(mass, 1, 0.5)
ode.BodySetMass(body, mass)
ode.GeomSetBody(geom, body)
ode.BodySetPosition(body, 0, 3, 0)

function physicsStep()
	ode.SpaceCollide(space, function(o1, o2)
		local b1 = ode.GeomGetBody(o1)
		local b2 = ode.GeomGetBody(o2)
		local contact = ode.ContactCreate()
		ode.ContactSurfaceSetMode(contact, ode.ContactBounce + ode.ContactSoftCFM)
		ode.ContactSurfaceSetMu(contact, ode.Infinity)
		ode.ContactSurfaceSetBounce(contact, 0.9)
		ode.ContactSurfaceSetBounceVel(contact, 0.1)
		ode.ContactSurfaceSetSoftCFM(contact, 0.001)
		local collisionCount = ode.Collide(o1, o2, contact)
		if collisionCount > 0 then
			local joint = ode.JointCreateContact(world, contactgroup, contact)
			ode.JointAttach(joint, b1, b2)
		end
	end)
	ode.WorldQuickStep(world, 0.01)
	ode.JointGroupEmpty(contactgroup)
end


--====== matrices ======--

function setVector(vector, x, y, z)
	honey.glm.vec3_set(vector, 0, x)
	honey.glm.vec3_set(vector, 1, y)
	honey.glm.vec3_set(vector, 2, z)
end

local view = honey.glm.mat4()
honey.glm.mat4_identity(view)
local translation = honey.glm.vec3()
setVector(translation, 0, -1, -6)
honey.glm.translate(view, translation)



--====== main loop ======--

local ballPosition = honey.glm.vec3()
setVector(ballPosition, ode.BodyGetPosition(body))

local time = 0
local dtAverage = 0
local dtCount = 0

while not window.shouldClose(w) do
	if window.getKey(w, window.KEY_ESCAPE) == window.PRESS then
		break
	end

	local newTime = window.getTime()
	local dt = newTime - time
	dtAverage = dtAverage + dt
	dtCount = dtCount + 1
	if dtCount > 60 then
		local fps = dtCount/dtAverage
		print(string.format('%0.2f fps', fps))
		dtAverage = 0
		dtCount = 0
	end
	time = newTime

	physicsStep()

	gl.ClearColor(0.2, 0.3, 0.3, 1.0)
	gl.Clear(gl.COLOR_BUFFER_BIT + gl.DEPTH_BUFFER_BIT)

	setVector(ballPosition, ode.BodyGetPosition(body))
	ball:SetPosition(ballPosition)

	shader:Use()
	shader:SetMatrix('model', ball.transform)
	shader:SetMatrix('view', view)
	shader:SetMatrix('projection', projection)
	

	ball:Draw()

	window.swapBuffers(w)
	window.pollEvents()
end

--===== shut down =====--

window.destroy(w)
gl.Terminate()
