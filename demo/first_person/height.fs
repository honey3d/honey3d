#version 330 core

in vec3 pos;
in vec3 normal;
in vec2 uv; 
  
uniform sampler2D grass; 

out vec4 fragment_color; 


void main()
{
    vec4 tex = texture(grass, uv);
    vec4 grey = vec4(0.3, 0.3, 0.3, 1.0);
    float steepness = dot(vec3(0, 1, 0), normal);
    fragment_color = mix(tex, grey, steepness);
}
