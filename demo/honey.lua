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
out vec3 pos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    pos = aPos;
}
]]

local fragmentShaderSource = [[
#version 330 core
in vec3 pos;
out vec4 FragColor;

void main()
{
	FragColor = vec4(pos.x+0.5, 0.0f, 2*(pos.y+pos.x), 1.0f);
}
]]

local vertexShader = gl.createShader(gl.shaderType.vertexShader)
gl.setShaderSource(vertexShader, vertexShaderSource)
gl.compileShader(vertexShader)
local fragmentShader = gl.createShader(gl.shaderType.fragmentShader)
gl.setShaderSource(fragmentShader, fragmentShaderSource)
gl.compileShader(fragmentShader)

local shader = gl.createProgram()
gl.programAttachShader(shader, vertexShader)
gl.programAttachShader(shader, fragmentShader)
gl.linkProgram(shader)
gl.deleteShader(vertexShader)
gl.deleteShader(fragmentShader)


local vertices = {
    -0.5, -0.5, 0.0,
     0.5, -0.5, 0.0,
     0.0,  0.5, 0.0
}  

local vertexArray = gl.createVertexArray()

local vertexBuffer = gl.createBuffer()
gl.bindVertexArray(vertexArray)

gl.bindBuffer(gl.bufferTarget.arrayBuffer, vertexBuffer)
local err = gl.getError()
if err ~= gl.errorType.noError then error(gl.errorName(err)) end
gl.bufferData(gl.bufferTarget.arrayBuffer, vertices, gl.bufferUsage.staticDraw)
if gl.getError() ~= gl.errorType.noError then error(gl.getError()) end

gl.vertexAttribPointer(0, 3, false, 3, 0)
if gl.getError() ~= gl.errorType.noError then error(gl.getError()) end
gl.vertexArrayEnableAttrib(0)
if gl.getError() ~= gl.errorType.noError then error(gl.getError()) end

gl.bindBuffer(gl.bufferTarget.arrayBuffer, 0)
if gl.getError() ~= gl.errorType.noError then error(gl.getError()) end

while not window.shouldClose(w) do
	gl.setClearColor(0.2, 0.3, 0.3, 1.0)
	gl.clear(gl.bufferMask.colorBuffer);

	gl.useProgram(shader)
	gl.bindVertexArray(vertexArray)
	gl.drawArrays(gl.primitiveType.triangles, 0, 3)

	window.swapBuffers(w)
	window.pollEvents()
end
window.destroy(w)
gl.terminate()
