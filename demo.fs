#version 330 core

in vec2 texture_coordinate;

uniform vec3 light_color;

uniform sampler2D box_texture;
uniform sampler2D happy_texture;

out vec4 fragment_color;

void main()
{
  fragment_color = texture(box_texture, texture_coordinate) * vec4(light_color.xyz, 1.0);
}
