#version 330 core

layout (location = 2) out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;


uniform sampler2D ParallaxTexture;



void main()
{     
	vec3 color = texture(ParallaxTexture, TexCoords).rgb;
	FragColor = vec4(color, 1.0);

}