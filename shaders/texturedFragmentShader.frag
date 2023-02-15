#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float Opacity;
in float Lighting;

uniform sampler2D texture1;

void main()
{
    FragColor = vec4(vec3(texture(texture1, TexCoord)), Opacity);
    FragColor.x *= Lighting;
    FragColor.y *= Lighting;
    FragColor.z *= Lighting;
}