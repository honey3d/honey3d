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
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
]]

local fragmentShaderSource = [[
#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
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


----------------------------------------------------------------

local texture = gl.texture.create()
gl.texture.bind(gl.texture.bindTarget.texture2d, texture)
err = gl.getError()
if err ~= gl.errorType.noError then error(gl.errorName(err)) end


local image, width, height, channels = honey.image.load('container.jpg', 0)
gl.texture.bufferImage2d(
	gl.texture.bindTarget.texture2d, 0,
	gl.texture.format.rgb,
	width, height,
	gl.texture.format.rgb, gl.dataType.uchar,
	image
)
gl.texture.generateMipmaps(gl.texture.bindTarget.texture2d)
err = gl.getError()
if err ~= gl.errorType.noError then error(gl.errorName(err)) end

honey.image.destroy(image)


local vertices = {
	-- position          color      uvs
	 0.5,  0.5, 0.0,    0, 0, 0,    1, 1,
	 0.5, -0.5, 0.0,    1, 0, 0,    1, 0,
	-0.5, -0.5, 0.0,    0, 1, 0,    0, 0,
	-0.5,  0.5, 0.0,    0, 0, 1,    0, 1
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

gl.data.vertexAttribPointer(0, 3, false, 8, 0)
gl.data.vertexArrayEnableAttrib(0)
gl.data.vertexAttribPointer(1, 3, false, 8, 3)
gl.data.vertexArrayEnableAttrib(1)
gl.data.vertexAttribPointer(2, 2, false, 8, 6)
gl.data.vertexArrayEnableAttrib(2)

gl.data.bindBuffer(gl.data.bufferTarget.arrayBuffer, 0)
if gl.getError() ~= gl.errorType.noError then error(gl.getError()) end

gl.shader.use(shader)
local textureLocation = gl.shader.getUniformLocation(shader, "ourTexture")
err = gl.getError()
if err ~= gl.errorType.noError then error(gl.errorName(err)) end
gl.shader.uniform1i(textureLocation, 0)
err = gl.getError()
if err ~= gl.errorType.noError then error(gl.errorName(err)) end


while not window.shouldClose(w) do
	gl.draw.setClearColor(0.2, 0.3, 0.3, 1.0)
	gl.draw.clear(gl.draw.bufferMask.colorBuffer);

	gl.texture.setActiveUnit(0)
	err = gl.getError()
	if err ~= gl.errorType.noError then error(gl.errorName(err)) end
	gl.texture.bind(gl.texture.bindTarget.texture2d, texture)
	err = gl.getError()
	if err ~= gl.errorType.noError then error(gl.errorName(err)) end


	gl.shader.use(shader)
	gl.data.bindVertexArray(vertexArray)
	gl.draw.drawElements(gl.draw.primitiveType.triangles, 6, gl.dataType.uint, 0)

	window.swapBuffers(w)
	window.pollEvents()
end
window.destroy(w)
gl.terminate()
