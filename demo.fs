#version 330 core

in vec2 texture_coordinate;

uniform sampler2D box_texture;
uniform sampler2D happy_texture;

out vec4 FragColor;

void main()
{
  FragColor = mix(texture(box_texture, texture_coordinate), texture(happy_texture, vec2(1,1)-texture_coordinate), 0.2);
}
