#version 330 core

in vec3 normal;
in vec2 texture_coordinate;
in vec3 fragment_position;

uniform vec3 ambient_color;

uniform vec3 light_color;
uniform vec3 light_position;

uniform sampler2D box_texture;
uniform sampler2D happy_texture;

uniform mat4 model;
uniform mat4 view;

out vec4 fragment_color;

void main()
{
  /* diffuse light */
  vec3 norm = normalize(normal);
  vec3 light_pos = vec3(view * vec4(light_position.xyz, 1.0));
  vec3 light_direction = normalize(light_pos - fragment_position);
  float diffuse = max( dot(norm, light_direction), 0 );
  vec3 diffuse_light = light_color * diffuse;

  /* specular reflection */
  vec3 view_direction = normalize(-fragment_position);
  vec3 reflection_direction = reflect(-light_direction, norm);
  float specular = pow(max(dot(view_direction, reflection_direction), 0), 32);
  vec3 specular_light = 1.0 * specular * light_color;

  vec4 total_light = vec4((ambient_color + diffuse_light + specular_light).xyz, 1.0);
  fragment_color = total_light * texture(box_texture, texture_coordinate);
}              
