local Mesh = {}
local gl = honey.gl
setmetatable(Mesh, {__index=_G})
setfenv(1, Mesh)


--===== creation =====--

local function loadScene(filename)
	local scene = honey.import.importFile(filename)
	local mesh = scene.meshes[1]
	local vertices = {}

	for i=1,#mesh.vertices do
		local position = mesh.vertices[i]
		local uv = mesh.uvs[1][i]
		table.insert(vertices, position.x)
		table.insert(vertices, position.y)
		table.insert(vertices, position.z)
		table.insert(vertices, uv.x)
		table.insert(vertices, uv.y)
	end

	local elements = {}
	for _, face in ipairs(mesh.faces) do
		assert(#face == 3)
		for _, i in ipairs(face) do
			table.insert(elements, i)
		end
	end

	return vertices, elements
end


function Load(filename)
	local self = {}
	setmetatable(self, {__index=Mesh})

	self.transform = honey.glm.mat4()
	honey.glm.mat4_identity(self.transform)

	-- opengl mesh data
	self.vertexArray = gl.GenVertexArrays()
	self.vertexBuffer = gl.GenBuffers()
	self.elementBuffer = gl.GenBuffers()

	-- load data
	local vertices, elements = loadScene(filename)
	self.elementCount = #elements

	-- buffer data
	gl.BindVertexArray(self.vertexArray)
	gl.BindBuffer(gl.ARRAY_BUFFER, self.vertexBuffer)
	gl.BufferData(gl.ARRAY_BUFFER, gl.FLOAT, vertices, gl.STATIC_DRAW)

	gl.BindBuffer(gl.ELEMENT_ARRAY_BUFFER, self.elementBuffer)
	gl.BufferData(gl.ELEMENT_ARRAY_BUFFER, gl.UNSIGNED_INT, elements, gl.STATIC_DRAW)

	-- set vertex attributes
	-- position
	gl.VertexAttribPointer(0, 3, false, 5, 0)
	gl.EnableVertexAttribArray(0)
	-- uvs
	gl.VertexAttribPointer(1, 2, false, 5, 3)
	gl.EnableVertexAttribArray(1)

	return self
end


--===== methods =====--

local function vectorToTable(v)
	local tbl = {
		x = honey.glm.vec3_get(v, 0),
		y = honey.glm.vec3_get(v, 1),
		z = honey.glm.vec3_get(v, 2),
	}
	return tbl
end

function SetPosition(self, position)
	honey.glm.mat4_identity(self.transform)
	honey.glm.translate(self.transform, position)
end


function Draw(self)
	gl.BindVertexArray(self.vertexArray)
	gl.DrawElements(gl.TRIANGLES, self.elementCount, gl.UNSIGNED_INT, 0)
end


--===== fin =====--

return Mesh
