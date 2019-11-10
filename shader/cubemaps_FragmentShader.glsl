#version 410 core
out vec4 FragColor;

uniform sampler2D texture1;
uniform samplerCube skybox;
uniform vec3 cameraPos;

in vec2 TexCoords;
in vec3 Position;
in vec3 Normal;



void main()
{
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(Position - cameraPos);
    vec3 R = refract(I, normalize(Normal), ratio);
    FragColor = vec4( texture(skybox, R).rgb , 1.0);
    // FragColor = vec4( texture(texture1, TexCoords).rgb, 1.0);

}
