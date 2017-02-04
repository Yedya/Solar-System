#version 330

in vec2 TexCoord0;
in vec4 LightIntensity0;

out vec4 FragColor;

uniform sampler2D gTextureSampler;
uniform vec4 gColor; // Uniform variable vec4
uniform vec4 gKa;

void main()
{
    FragColor = gColor * LightIntensity0;
	
}