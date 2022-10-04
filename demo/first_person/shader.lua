local Shader = {}
local gl = honey.gl
setmetatable(Shader, {__index=_G})
setfenv(1, Shader)


--===== creation =====--

function Create(vertexSource, fragmentSource)
	local self = {}
	setmetatable(self, {__index=Shader})

	-- vertex shader
	local vertexShader = gl.CreateShader(gl.VERTEX_SHADER)
	gl.ShaderSource(vertexShader, vertexSource)
	gl.CompileShader(vertexShader)
	
	-- fragment shader
	local fragmentShader = gl.CreateShader(gl.FRAGMENT_SHADER)
	gl.ShaderSource(fragmentShader, fragmentSource)
	gl.CompileShader(fragmentShader)
	
	-- link
	self.program = gl.CreateProgram()
	gl.AttachShader(self.program, vertexShader)
	gl.AttachShader(self.program, fragmentShader)
	gl.LinkProgram(self.program)

	-- clean up
	gl.DeleteShader(vertexShader)
	gl.DeleteShader(fragmentShader)

	return self
end


function Load(vertexFile, fragmentFile)
	local vf = io.open(vertexFile)
	local vsource = vf:read('*a')
	vf:close()

	local ff = io.open(fragmentFile)
	local fsource = ff:read('*a')
	ff:close()

	return Create(vsource, fsource)
end


--===== methods =====--

function Use(self)
	gl.UseProgram(self.program)
end

function SetMatrix(self, name, matrix)
	gl.UseProgram(self.program)
	local location = gl.GetUniformLocation(self.program, name)
	gl.UniformMatrix4fv(location, false, matrix)
end


function SetTexture(self, name, texture)
	self:Use()
	gl.BindTexture(gl.TEXTURE_2D, texture)
	local location = gl.GetUniformLocation(self.program, name)
	gl.Uniform1i(location, 0)
end


--===== fin =====--

return Shader
