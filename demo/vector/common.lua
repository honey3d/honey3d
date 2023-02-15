honey.run = function()
	local gl = honey.gl
	local window = honey.window

	-- initialize opengl
	gl.Init()
	window.setHint(window.hintType.contextVersionMajor, 3)
	window.setHint(window.hintType.contextVersionMinor, 3)
	
	local win = window.create(640, 480, 'first person demo')
	honey.window.win = win
	window.makeContextCurrent(win)
	gl.InitGlad()
	gl.Enable(gl.DEPTH_TEST)

	if honey.init then
		honey.init()
	end

	window.setFramebufferSizeCallback(win, function(_, width, height)
		if honey.windowSizeCallback then
			honey.windowSizeCallback(width, height)
		end
	end)

	local time = 0
	drawTime = 1/60
	while not window.shouldClose(win) do
		local t = window.getTime()
		local dt = t-time
		time = t

		honey.update(dt)
		window.pollEvents()

		if time > drawTime then
			if honey.clearColor then
				gl.ClearColor(
					honey.clearColor.r,
					honey.clearColor.g,
					honey.clearColor.b,
					1.0
				)
			else
				gl.ClearColor(0.2, 0.3, 0.3, 1.0)
			end
			gl.Clear(gl.COLOR_BUFFER_BIT + gl.DEPTH_BUFFER_BIT)
			honey.draw()
			window.swapBuffers(win)
			drawTime = drawTime + 1/60
		end
	end

	window.destroy(win)
	gl.Terminate()
end


local set = honey.glm.vec3_set
local get = honey.glm.vec3_get
function honey.glm.setVector(vec, x, y, z)
	set(vec, 0, x)
	set(vec, 1, y)
	set(vec, 2, z)
end


function honey.glm.makeVector(x, y, z)
	local v = honey.glm.vec3()
	honey.glm.setVector(v, x, y, z)
	return v
end


function honey.glm.vec3_tostring(v)
	return string.format(
		'[%0.2f, %0.2f, %0.2f]',
		get(v, 0), get(v, 1), get(v, 2)
	)
end
