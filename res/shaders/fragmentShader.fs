#version 330 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D Texture;
uniform sampler2D Texture2;
uniform float mixVal;

void main()
{
	FragColor = mix(texture(Texture, TexCoord), texture(Texture2, TexCoord), mixVal);
}