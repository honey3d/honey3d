local gl = honey.gl
local window = honey.window


--===== initialize audio =====--

local engine = honey.audio.engine_init()
honey.audio.engine_play_sound(engine, 'example_sound.ogg')


--====== initialize opengl ======--

gl.Init()
window.setHint(window.hintType.contextVersionMajor, 3)
window.setHint(window.hintType.contextVersionMinor, 3)
window.setHint(window.hintType.openGlProfile, window.profileType.openGlCoreProfile)


--====== create window ======--

local w = window.create(640, 480, 'hello, world!')
window.makeContextCurrent(w)
gl.InitGlad()
gl.Enable(gl.DEPTH_TEST)

window.setFramebufferSizeCallback(w, function(_, width, height)
	print(string.format("resize: (%d, %d)", width, height))
	gl.Viewport(0, 0, width, height)
end)


--====== compile shaders ======--

local vertexShaderSource = [[
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
]]

local fragmentShaderSource = [[
#version 330 core
out vec4 FragColor;
  
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


--====== set up mesh data manually ======--

local vertices = {
--     positions          uvs   
	 0.5,  0.5, 0.0,   1.0, 1.0, -- top right
	 0.5, -0.5, 0.0,   1.0, 0.0, -- bottom right
	-0.5, -0.5, 0.0,   0.0, 0.0, -- bottom let
	-0.5,  0.5, 0.0,   0.0, 1.0  -- top let 
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
gl.VertexAttribPointer(0, 3, false, 5, 0)
gl.EnableVertexAttribArray(0)

-- uv
gl.VertexAttribPointer(1, 2, false, 5, 3)
gl.EnableVertexAttribArray(1)


--===== load mesh from file =====--

local scene = honey.import.importFile('suzanne.dae')
local mesh = scene.meshes[1]
local suzanne = {}
suzanne.vertices = {}
print('mesh.vertices', #mesh.vertices)
for i=1,#mesh.vertices do
	local position = mesh.vertices[i]
	local uv = mesh.uvs[1][i]
	table.insert(suzanne.vertices, position.x)
	table.insert(suzanne.vertices, position.y)
	table.insert(suzanne.vertices, position.z)
	table.insert(suzanne.vertices, uv.x)
	table.insert(suzanne.vertices, uv.y)
end
suzanne.indices = {}
for _, face in ipairs(mesh.faces) do
	assert(#face == 3)
	for _, i in ipairs(face) do
		table.insert(suzanne.indices, i)
	end
end
print('mesh.faces', #mesh.faces)
print('suzanne.indices', #suzanne.indices)

suzanne.vertexArr = gl.GenVertexArrays()
suzanne.vertexBuf = gl.GenBuffers()
suzanne.elementBuf = gl.GenBuffers()

gl.BindVertexArray(suzanne.vertexArr)
gl.BindBuffer(gl.ARRAY_BUFFER, suzanne.vertexBuf)
gl.BufferData(gl.ARRAY_BUFFER, gl.FLOAT, suzanne.vertices, gl.STATIC_DRAW)

gl.BindBuffer(gl.ELEMENT_ARRAY_BUFFER, suzanne.elementBuf)
gl.BufferData(gl.ELEMENT_ARRAY_BUFFER, gl.UNSIGNED_INT, suzanne.indices, gl.STATIC_DRAW)

gl.VertexAttribPointer(0, 3, false, 5, 0)
gl.EnableVertexAttribArray(0)
gl.VertexAttribPointer(1, 2, false, 5, 3)
gl.EnableVertexAttribArray(1)


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


--===== generate cairo texture =====--

local image = honey.image
local surface = image.surface_create(image.FORMAT_ARGB32, 512, 512)
local cr = image.context_create(surface)
image.context_select_font_face(cr, "sans-serif", image.FONT_SLANT_NORMAL, image.FONT_WEIGHT_NORMAL)
image.context_set_font_size(cr, 32)
image.context_set_source_rgb(cr, 1, 0, 0)
image.context_move_to(cr, 100, 100)
image.context_show_text(cr, "hello, world!")
local data = image.surface_get_data(surface)
gl.BindTexture(gl.TEXTURE_2D, texture)
gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_SWIZZLE_R, gl.BLUE)
gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_SWIZZLE_B, gl.RED)
--gl.TexParameteri(gl.TEXTURE_2D, gl.TEXTURE_SWIZZLE_A, gl.RED)
gl.TexImage2D(
	gl.TEXTURE_2D, 0,
	gl.RGB, width, height,
	gl.RGBA, gl.UNSIGNED_BYTE,
	data
)
gl.GenerateMipmap(gl.TEXTURE_2D)


--====== matrices ======--

local model = honey.glm.mat4()
local axis1 = honey.glm.vec3()
honey.glm.vec3_set(axis1, 0, 1.0)
honey.glm.vec3_set(axis1, 1, 0.0)
honey.glm.vec3_set(axis1, 2, 0.0)

local axis2 = honey.glm.vec3()
honey.glm.vec3_set(axis2, 0, 0.0)
honey.glm.vec3_set(axis2, 1, 1.0)
honey.glm.vec3_set(axis2, 2, 0.0)

local view = honey.glm.mat4()
honey.glm.mat4_identity(view)
local translation = honey.glm.vec3()
honey.glm.vec3_set(translation, 0,  0.0)
honey.glm.vec3_set(translation, 1,  0.0)
honey.glm.vec3_set(translation, 2, -3.0)
honey.glm.translate(view, translation)

local projection = honey.glm.mat4()
honey.glm.perspective(math.rad(45), 800/600, 0.1, 100, projection)


--====== main loop ======--

local transform = honey.glm.mat4()

while not window.shouldClose(w) do
	local time = window.getTime()

	gl.ClearColor(0.2, 0.3, 0.3, 1.0)
	gl.Clear(gl.COLOR_BUFFER_BIT + gl.DEPTH_BUFFER_BIT)

	gl.ActiveTexture(0)
	gl.BindTexture(gl.TEXTURE_2D, texture)

	gl.UseProgram(shader)
	
	local modelL = gl.GetUniformLocation(shader, 'model')
	local viewL = gl.GetUniformLocation(shader, 'view')
	local projectionL = gl.GetUniformLocation(shader, 'projection')
	
	honey.glm.mat4_identity(model)
	honey.glm.rotate(model, 0.5*math.pi*time, axis2)
	honey.glm.rotate(model, math.rad(-90), axis1)

	gl.UniformMatrix4fv(modelL, false, model)
	gl.UniformMatrix4fv(viewL, false, view)
	gl.UniformMatrix4fv(projectionL, false, projection)

	--gl.BindVertexArray(vertexArray)
	--gl.DrawElements(gl.TRIANGLES, 6, gl.UNSIGNED_INT, 0)

	gl.BindVertexArray(suzanne.vertexArr)
	gl.DrawElements(gl.TRIANGLES, 3*#mesh.faces, gl.UNSIGNED_INT, 0)

	window.swapBuffers(w)
	window.pollEvents()
end

--===== shut down =====--

window.destroy(w)
gl.Terminate()
honey.audio.engine_uninit(engine)
image.surface_destroy(surface)
image.context_destroy(cr)
