#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float Opacity;
in float Lighting;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord) * Lighting;
    FragColor.a = Opacity;
}