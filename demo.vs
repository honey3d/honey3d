#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 texCoord;

out vec2 texture_coordinate;
out vec3 normal;
out vec3 fragment_position;

uniform mat4 model;
uniform mat3 normal_mat;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(position.xyz, 1.0);
  texture_coordinate = texCoord;
  normal = mat3(view) * normal_mat * in_normal;
  fragment_position = vec3(view * model * vec4(position.xyz, 1.0));
}