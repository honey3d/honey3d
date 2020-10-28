local Vec3, Vec4 = require('Vector')()
local Mat3, Mat4 = require('Matrix')()

local m = Mat3.new{1, 0, 1,
                   0, 1, 0,
                   0, 0, 0}
print(Mat3.tostring(m))

honey.input.key.bind(honey.input.key.escape, honey.exit)

local basis = function(matrix)
    local b = {}
    b.x = Vec3.new{1, 0, 0}
    b.y = Vec3.new{0, 1, 0}
    b.z = Vec3.new{0, 0, 1}

    local mat3 = honey.cglm.new_array_zero(9)
    honey.cglm.mat4.pick3(matrix, mat3)

    honey.cglm.mat3.mulv(b.x, mat3, b.x)
    honey.cglm.mat3.mulv(b.y, mat3, b.y)
    honey.cglm.mat3.mulv(b.z, mat3, b.z)

    return b
end

local vertex_shader = [[
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coord;

out vec2 uv_coord;
out vec3 v_normal;
out vec3 v_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(position.xyz, 1);
  uv_coord = tex_coord;
  v_normal = mat3(view) * normal;
  v_position = vec3(view * model * vec4(position.xyz, 1.0));
} ]]
local fragment_shader = [[
#version 330 core
uniform vec4 base_color;

out vec4 color;
void main() { color = base_color; } ]]

local shader = honey.shader.new(vertex_shader, fragment_shader)
local plane = honey.primitives.plane(2,2)

local color1 = Vec4.new{1,0,0,1}
local color2 = Vec4.new{0,0,1,1}
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
