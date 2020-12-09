local VertexCode = [[
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 4) in vec2 uv;

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

SpatialShader.prototype.use = function(self)
   self.shader:use()
end

SpatialShader.prototype.setInteger = function(self, name, value)
   self.shader:setInteger(name, value)
end

SpatialShader.prototype.setFloat = function(self, name, value)
   self.shader:setFloat(name, value)
end

SpatialShader.prototype.setVec3 = function(self, name, value)
   self.shader:setVec3(name, value)
end

SpatialShader.prototype.setVec4 = function(self, name, value)
   self.shader:setVec4(name, value)
end

SpatialShader.prototype.setMat3 = function(self, name, value)
   self.shader:setMat3(name, value)
end

SpatialShader.prototype.setMat4 = function(self, name, value)
   self.shader:setMat4(name, value)
end

SpatialShader.prototype.setCamera = function(self, camera)
   self.shader:setMat4('view', camera.view)
   self.shader:setMat4('projection', camera.projection)
end

SpatialShader.prototype.drawMesh = function(self, meshInstance)
   self.shader:setMat4('model', meshInstance.transform)
   self.albedo:use(0)
   meshInstance.mesh:draw(self.shader)
end

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SpatialShader.mt = {}
SpatialShader.mt.__index = SpatialShader.prototype

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SpatialShader.new = function(albedo)
   local spatialshader = {}
   spatialshader.shader = honey.shader(VertexCode, FragmentCode)
   spatialshader.albedo = albedo

   setmetatable(spatialshader, SpatialShader.mt)

   return spatialshader
end

return SpatialShader
