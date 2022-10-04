#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal_;
layout (location = 2) in vec2 uv_;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 pos;
out vec3 normal;
out vec2 uv;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    pos = vec3(gl_Position);
    normal = normal_;
    uv = uv_;
}
