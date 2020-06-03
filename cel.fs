#version 330 core

/* input from the vector shader */
in vec3 in_normal;
in vec2 in_texture_coordinate;
in vec3 in_fragment_position;

/* light uniforms */
uniform vec3 ambient_color;

struct point_light {
  vec3 position; /* view position */

  float constant;
  float linear;
  float quadratic;

  vec3 color;
};

struct directional_light {
  vec3 direction;
  vec3 color;
};

#define MAX_POINT_LIGHTS 8
#define MAX_DIRECTIONAL_LIGHTS 8

uniform point_light point_lights[MAX_POINT_LIGHTS];
uniform int n_point_lights;

uniform directional_light directional_lights[MAX_DIRECTIONAL_LIGHTS];
uniform int n_directional_lights;

/* texture uniforms */
uniform sampler2D tex;

/* view matrix */
uniform mat4 view;

out vec4 fragment_color;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* compute phong cel-shader intensity */
float compute_light_intensity(vec3 normal, vec3 light_direction, vec3 view_direction) {
  /* diffuse light */
  float diffuse_intensity = max(dot(normal, light_direction), 0);
  diffuse_intensity = smoothstep(0, 0.01, diffuse_intensity);

  /* specular highlight */
  vec3 reflection_direction = reflect(-light_direction, normal);
  float specular_intensity = pow(max(dot(view_direction, reflection_direction), 0), 256);
  specular_intensity = smoothstep(0.005, 0.01, specular_intensity);

  return diffuse_intensity + specular_intensity;
}

/* compute directional light contribution */
vec3 compute_directional_light(directional_light light, vec3 normal, vec3 view_direction) {
  vec3 light_direction = -vec3(view * vec4(light.direction.xyz, 0.0));
  return light.color * compute_light_intensity(normal, light_direction, view_direction);
}

/* compute point light contribution */
vec3 compute_point_light(point_light light, vec3 normal, vec3 fragment_position, vec3 view_direction) {
  vec3 light_position = vec3(view * vec4(light.position.xyz, 1.0));
  vec3 light_direction = normalize(light_position - fragment_position);

  float light_intensity = compute_light_intensity(normal, light_direction, view_direction);

  /* attenuation */
  float distance = length(light_position - fragment_position);
  float attenuation = 1.0 / (light.constant +
                             light.linear * distance +
                             light.quadratic * distance * distance);

  return attenuation * light.color * light_intensity;
}

void main()
{
  vec3 normal = normalize(in_normal);
  vec3 view_direction = normalize(-in_fragment_position);
  
  vec3 point_light_contrib = vec3(0, 0, 0);
  for (int i=0; i<n_point_lights; i++) {
    point_light_contrib += compute_point_light(point_lights[i],
                                               normal,
                                               in_fragment_position,
                                               view_direction);
  }

  vec3 directional_light_contrib = vec3(0,0,0);
  for (int i=0; i<n_directional_lights; i++) {
    directional_light_contrib += compute_directional_light(directional_lights[i],
                                                           normal,
                                                           view_direction);
  }
  
  /* rim lighting */
  /*float rim_amount = 0.716;
  float rim_threshold = 0.5;
  float rim_norm = 1 - dot(normal, view_direction);
  rim_intensity = smoothstep(rim_amount - 0.01, rim_amount + 0.01, rim_intensity);
  vec3 rim_light = rim_intensity * ambient_color;*/

  vec4 total_light = vec4((ambient_color + point_light_contrib + directional_light_contrib).xyz, 1.0);
  fragment_color = total_light * texture(tex, in_texture_coordinate); 
}              
