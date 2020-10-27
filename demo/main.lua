for k, v in pairs(honey.shader) do
    print(k, v)
end

honey.input.key.bind(honey.input.key.escape, honey.exit)

local vertex_shader = [[
#version 330 core

layout(location = 0) in vec3 position;

void main()
{
  gl_Position.xyz = position;
  gl_Position.w = 1.0;
} ]]
local fragment_shader = [[
#version 330 core

out vec4 color;
void main() { color = vec4(1,0,0,1); } ]]

local shader = honey.shader.new(vertex_shader, fragment_shader)
local plane = honey.primitives.plane(1,1)

function honey.update(dt)
end

function honey.draw()
    honey.mesh.draw(plane, shader)
end
