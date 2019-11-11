#version 410 core

in vec3 normal;
out vec4 color;

float near = 0.1;
float far  = 100.0;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}
void main()
{
  // color = vec4(vec3(clamp(dot(normalize(normal), vec3(0,0,1)), 0, 1)), 1.0);
  // float linearDepth = (2.0 * near * far) / (far + near - z * (far - near));
  // color = (1-LinearizeDepth(gl_FragCoord.z))*vec4(normalize(normal)*0.5+0.5, 1.0);
  color = vec4(normalize(normal)*0.5+0.5, 1.0);
  // color = vec4(vec3(1-gl_FragCoord.z), 1.0);
}
