#version 330 core


in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

uniform sampler2D inputTexture;
uniform vec3 viewPosition;

out vec4 FragColor;




void main(){

	vec3 result = texture(inputTexture, TexCoords).rgb;

	FragColor = vec4(result, 1.0f);



    
	
}