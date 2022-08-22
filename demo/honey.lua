local gl = honey.gl
local window = honey.window

gl.errorName = function(errorCode)
	for name, code in pairs(gl.errorType) do
		if code == errorCode then return name end
	end
	return 'unknown'
end

gl.init()
window.setHint(window.hintType.contextVersionMajor, 3)
window.setHint(window.hintType.contextVersionMinor, 3)
window.setHint(window.hintType.openGlProfile, window.profileType.openGlCoreProfile)

local w = window.create(640, 480, 'hello, world!')
window.makeContextCurrent(w)
gl.initGlad()

window.setFramebufferSizeCallback(w, function(_, width, height)
	print(string.format("resize: (%d, %d)", width, height))
	gl.setViewport(0, 0, width, height)
end)


local vertexShaderSource = [[
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 pColor;

void main()
{
    pColor = aColor;
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
]]

local fragmentShaderSource = [[
#version 330 core
in vec3 pColor;
uniform vec4 color;
out vec4 FragColor;

void main()
{
	FragColor = vec4(pColor.rgb, 1);
}
]]

local vertexShader = gl.shader.create(gl.shader.type.vertexShader)
gl.shader.setSource(vertexShader, vertexShaderSource)
gl.shader.compile(vertexShader)
local fragmentShader = gl.shader.create(gl.shader.type.fragmentShader)
gl.shader.setSource(fragmentShader, fragmentShaderSource)
gl.shader.compile(fragmentShader)

local shader = gl.shader.createProgram()
gl.shader.attachShader(shader, vertexShader)
gl.shader.attachShader(shader, fragmentShader)
gl.shader.link(shader)
gl.shader.delete(vertexShader)
gl.shader.delete(fragmentShader)


local vertices = {
	-- position          color
	 0.5,  0.5, 0.0,    0, 0, 0,
	 0.5, -0.5, 0.0,    1, 0, 0,
	-0.5, -0.5, 0.0,    0, 1, 0,
	-0.5,  0.5, 0.0,    0, 0, 1
}
local indices = {
        0, 1, 3,
        1, 2, 3
}

local vertexArray = gl.data.createVertexArray()

local vertexBuffer = gl.data.createBuffer()
local elementBuffer = gl.data.createBuffer()
gl.data.bindVertexArray(vertexArray)

gl.data.bindBuffer(gl.data.bufferTarget.arrayBuffer, vertexBuffer)
local err = gl.getError()
if err ~= gl.errorType.noError then error(gl.errorName(err)) end
gl.data.bufferData(gl.data.bufferTarget.arrayBuffer, gl.dataType.float, vertices, gl.data.bufferUsage.staticDraw)
if gl.getError() ~= gl.errorType.noError then error(gl.getError()) end

gl.data.bindBuffer(gl.data.bufferTarget.elementArrayBuffer, elementBuffer)
gl.data.bufferData(gl.data.bufferTarget.elementArrayBuffer, gl.dataType.uint, indices, gl.data.bufferUsage.staticDraw)

gl.data.vertexAttribPointer(0, 3, false, 6, 0)
gl.data.vertexArrayEnableAttrib(0)
gl.data.vertexAttribPointer(1, 3, false, 6, 3)
gl.data.vertexArrayEnableAttrib(1)

gl.data.bindBuffer(gl.data.bufferTarget.arrayBuffer, 0)
if gl.getError() ~= gl.errorType.noError then error(gl.getError()) end

while not window.shouldClose(w) do
	gl.draw.setClearColor(0.2, 0.3, 0.3, 1.0)
	gl.draw.clear(gl.draw.bufferMask.colorBuffer);

	gl.shader.use(shader)
	local time = window.getTime()
	local greenValue = (math.sin(time) / 2) + 0.5 
	local colorLocation = gl.shader.getUniformLocation(shader, 'color')
	gl.shader.uniform4f(colorLocation, 0, greenValue, 0, 1)

	gl.data.bindVertexArray(vertexArray)
	gl.draw.drawElements(gl.draw.primitiveType.triangles, 6, gl.dataType.uint, 0)

	window.swapBuffers(w)
	window.pollEvents()
end
window.destroy(w)
gl.terminate()
