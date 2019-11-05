#version 410 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    // FragColor = texture(ourTexture, TexCoord);
    // mix function takes two values as input and linearly interpolates between them based on its third argument.
    FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.5);
}
