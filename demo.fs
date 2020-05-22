#version 330 core

in vec2 texture_coordinate;

uniform sampler2D box_texture;
uniform sampler2D happy_texture;

out vec4 FragColor;

void main()
{
  FragColor = mix(texture(box_texture, texture_coordinate),
                  vec4(texture(happy_texture, texture_coordinate).xyz, 1.0),
                  0.2);
}
