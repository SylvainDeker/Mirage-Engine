#version 410 core

in vec3 normal;
out vec4 color;

uniform vec4 usercolor;

void main()
{
  color = usercolor;
}
