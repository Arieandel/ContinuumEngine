#version 330
in  vec3 TexCoords;

out vec4 fragColor;
uniform samplerCube sceneCube;  

void main() { 

	fragColor =  texture(sceneCube, TexCoords);
	
}