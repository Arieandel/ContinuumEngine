#version 330 core
out vec4 FragColor;
  
in vec3 TexCoords;

uniform samplerCube sceneCube;
uniform samplerCube skybox;


void main()
{ 
	vec4 skyColor = texture(skybox, TexCoords);
	vec4 sceneColor = texture(sceneCube, TexCoords);

	skyColor += sceneColor;

    FragColor = skyColor;
	
	//vec4(skyColor, 1.0); 
}