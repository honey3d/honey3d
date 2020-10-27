for k, v in pairs(honey.shader) do
    print(k, v)
end

honey.input.key.bind(honey.input.key.escape, honey.exit)

local vec4 = function(v)
    local vector = honey.cglm.new_array_zero(4)
    honey.cglm.set_value(vector, 0, v[1])
    honey.cglm.set_value(vector, 1, v[2])
    honey.cglm.set_value(vector, 2, v[3])
    honey.cglm.set_value(vector, 3, v[4])
    return vector
end

local vertex_shader = [[
#version 330 core

layout(location = 0) in vec3 position;

void main()
{
  gl_Position.xyz = position - vec3(1,1,0);
  gl_Position.w = 1.0;
} ]]
local fragment_shader = [[
#version 330 core
uniform vec4 base_color;

out vec4 color;
void main() { color = base_color; } ]]

local shader = honey.shader.new(vertex_shader, fragment_shader)
local plane = honey.primitives.plane(2,2)

local color1 = vec4{1,0,0,1}
local color2 = vec4{0,0,1,1}
local color = honey.cglm.new_array_zero(4)

local total_time = 0

function honey.update(dt)
    total_time = total_time + dt
    honey.cglm.vec4.lerp(color1, color2, 0.5*(math.sin(math.pi*total_time)+1), color)
end

function honey.draw()
    honey.shader.set_vec4(shader, "base_color", color)
    honey.mesh.draw(plane, shader)
end
