local Shader = require('Shader')

local VertexCode = [[
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Position;
out vec3 Normal;
out vec2 UV;

void main()
{
    gl_Position = projection * view * model * vec4(position.xyz, 1);
    Position = gl_Position.xyz;
    Normal = normal;
    UV = uv;
} ]]

local FragmentCode = [[
#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;

uniform sampler2D albedo;

out vec4 color;

void main()
{
    color = vec4(texture(albedo, UV).xyz, 1);
} ]]

local SpatialShader = {}

SpatialShader.prototype = {}
setmetatable(SpatialShader.prototype, { __index = Shader.prototype })

SpatialShader.prototype.setCamera = function(self, camera)
   self:setMat4('view', camera.view)
   self:setMat4('projection', camera.projection)
end

SpatialShader.prototype.drawMesh = function(self, mesh)
   self:setMat4('model', mesh.transform)
   honey.texture.use(self.albedo, 0)
   honey.mesh.draw(mesh.mesh, self.program)
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SpatialShader.mt = {}
SpatialShader.mt.__index = SpatialShader.prototype

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SpatialShader.new = function(albedo)
   local spatialshader = Shader.new(VertexCode, FragmentCode)
   spatialshader.albedo = albedo

   setmetatable(spatialshader, SpatialShader.mt)

   return spatialshader
end

return SpatialShader
