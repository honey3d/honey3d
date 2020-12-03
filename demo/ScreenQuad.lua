local ScreenQuad = {}

ScreenQuad.quad = honey.primitives.plane(2,2)

local vertexShader = [[
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

out vec2 UV;

void main() 
{
  gl_Position = vec4(position.xy, 0, 1) - vec4(1,1,0,0);
  UV = uv;
} ]]

local fragmentShader = [[
#version 330 core

in vec2 UV;

uniform sampler2D tex;

out vec4 color;

void main()
{
  color = vec4(texture(tex, UV).xyz, 1);
} ]]

ScreenQuad.shader = honey.shader(vertexShader, fragmentShader)

ScreenQuad.tex   = honey.texture.new()
ScreenQuad.depth = honey.texture.new()
honey.texture.create(ScreenQuad.tex, 'rgb', 640, 480);
honey.texture.create(ScreenQuad.depth, 'depth', 640, 480);
--honey.texture.load(ScreenQuad.texture, 'checkerboard.png', false)

ScreenQuad.fb = honey.texture.new_framebuffer(ScreenQuad.tex, ScreenQuad.depth, 640, 480)

ScreenQuad.draw = function(self)
   honey.texture.use(self.tex, 0)
   honey.mesh.draw(self.quad, self.shader)
end

return ScreenQuad
