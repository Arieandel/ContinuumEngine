#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec3 Position;
out vec2 TexCoords;

void main(){


	gl_Position = vec4(position, 1.0f);
	Position = position;
	TexCoords = texCoords;
	
}