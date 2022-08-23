local gl = honey.gl
local window = honey.window


--====== initialize opengl ======--

gl.Init()
window.setHint(window.hintType.contextVersionMajor, 3)
window.setHint(window.hintType.contextVersionMinor, 3)
window.setHint(window.hintType.openGlProfile, window.profileType.openGlCoreProfile)


--====== create window ======--

local w = window.create(640, 480, 'hello, world!')
window.makeContextCurrent(w)
gl.InitGlad()

window.setFramebufferSizeCallback(w, function(_, width, height)
	print(string.format("resize: (%d, %d)", width, height))
	gl.setViewport(0, 0, width, height)
end)


--====== compile shaders ======--

local vertexShaderSource = [[
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
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

-- vertex shader
local vertexShader = gl.CreateShader(gl.VERTEX_SHADER)
gl.ShaderSource(vertexShader, vertexShaderSource)
gl.CompileShader(vertexShader)

-- fragment shader
local fragmentShader = gl.CreateShader(gl.FRAGMENT_SHADER)
gl.ShaderSource(fragmentShader, fragmentShaderSource)
gl.CompileShader(fragmentShader)

-- link
local shader = gl.CreateProgram()
gl.AttachShader(shader, vertexShader)
gl.AttachShader(shader, fragmentShader)
gl.LinkProgram(shader)
-- clean up
gl.DeleteShader(vertexShader)
gl.DeleteShader(fragmentShader)


--====== set up vertex data ======--

local vertices = {
--     positions          colors           uvs   
	 0.5,  0.5, 0.0,   1.0, 0.0, 0.0,   1.0, 1.0, -- top right
	 0.5, -0.5, 0.0,   0.0, 1.0, 0.0,   1.0, 0.0, -- bottom right
	-0.5, -0.5, 0.0,   0.0, 0.0, 1.0,   0.0, 0.0, -- bottom let
	-0.5,  0.5, 0.0,   1.0, 1.0, 0.0,   0.0, 1.0  -- top let 
}
local indices = {
    0, 1, 3, -- first triangle
    1, 2, 3  -- second triangle
}

-- buffers
local vertexArray = gl.GenVertexArrays()
local vertexBuffer = gl.GenBuffers()
local elementBuffer = gl.GenBuffers()

gl.BindVertexArray(vertexArray)

gl.BindBuffer(gl.ARRAY_BUFFER, vertexBuffer)
gl.BufferData(gl.ARRAY_BUFFER, gl.FLOAT, vertices, gl.STATIC_DRAW)

gl.BindBuffer(gl.ELEMENT_ARRAY_BUFFER, elementBuffer)
gl.BufferData(gl.ELEMENT_ARRAY_BUFFER, gl.UNSIGNED_INT, indices, gl.STATIC_DRAW)

-- position
gl.VertexAttribPointer(0, 3, false, 8, 0)
gl.EnableVertexAttribArray(0)

-- color
gl.VertexAttribPointer(1, 3, false, 8, 3)
gl.EnableVertexAttribArray(1)

-- uv
gl.VertexAttribPointer(2, 2, false, 8, 6)
gl.EnableVertexAttribArray(2)


--====== load texture ======--

local texture = gl.GenTextures()
gl.BindTexture(gl.TEXTURE_2D, texture)

gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.REPEAT)
gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.REPEAT)

gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR)
gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR)

local image, width, height = honey.image.load('container.jpg', 3)
gl.TexImage2D(
	gl.TEXTURE_2D, 0,
	gl.RGB, width, height,
	gl.RGB, gl.UNSIGNED_BYTE,
	image
)
gl.GenerateMipmap(gl.TEXTURE_2D)
honey.image.destroy(image)

-- connect shader samplers to texture units
gl.UseProgram(shader)
gl.Uniform1i(gl.GetUniformLocation(shader, 'ourTexture'), 0)


--====== main loop ======--

local transform = honey.glm.mat4()

while not window.shouldClose(w) do
	gl.ClearColor(0.2, 0.3, 0.3, 1.0)
	gl.Clear(gl.COLOR_BUFFER_BIT)

	gl.ActiveTexture(0)
	gl.BindTexture(gl.TEXTURE_2D, texture)

	gl.UseProgram(shader)
	honey.glm.mat4_identity(transform)
	local time = window.getTime()
	honey.glm.rotate_z(transform, time, transform)
	local transformLocation = gl.GetUniformLocation(shader, 'transform')
	gl.UniformMatrix4fv(transformLocation, false, transform)

	gl.BindVertexArray(vertexArray)
	gl.DrawElements(gl.TRIANGLES, 6, gl.UNSIGNED_INT, 0)

	window.swapBuffers(w)
	window.pollEvents()
end
window.destroy(w)
gl.Terminate()
