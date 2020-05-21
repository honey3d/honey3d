#version 330 core

in vec3 outColor;
in vec2 outTexCoord;

out vec4 FragColor;

uniform sampler2D boxTexture;
uniform sampler2D happyTexture;

void main()
{
  FragColor = vec4(outColor.xyz, 1.0); //mix(texture(boxTexture, outTexCoord), texture(happyTexture, outTexCoord), 0.2);
}
