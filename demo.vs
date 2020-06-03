#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 in_texture_coordinate;
out vec3 in_normal;
out vec3 in_fragment_position;

uniform mat4 model;
uniform mat3 normal_mat;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(position.xyz, 1.0);
  in_texture_coordinate = texCoord;
  in_normal = mat3(view) * normal_mat * normal;
  in_fragment_position = vec3(view * model * vec4(position.xyz, 1.0));
}