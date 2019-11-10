#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Position;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;
    Normal = mat3(transpose(inverse(model))) * inormal;  
    Position = aPos;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}