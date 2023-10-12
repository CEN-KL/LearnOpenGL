#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float taffy;

void main()
{
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2); 练习1
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), taffy);
}