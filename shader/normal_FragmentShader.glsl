#version 410 core

in vec3 normal;
out vec4 color;

void main()
{
  // color = vec4(vec3(clamp(dot(normalize(normal), vec3(0,0,1)), 0, 1)), 1.0);
  color = vec4(normalize(normal)*0.5+0.5, 1.0);
}