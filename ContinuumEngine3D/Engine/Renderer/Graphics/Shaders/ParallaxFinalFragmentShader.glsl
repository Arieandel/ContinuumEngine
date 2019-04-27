#version 330 core
out vec4 FragColor;

in vec3 Position;
in vec2 TexCoords;


//uniform sampler2D Midnight;
uniform sampler2D Land2;
//uniform sampler2D Land1;
//uniform sampler2D Trees;
//uniform sampler2D Sky;
//uniform sampler2D Stars;

void main()
{      
	vec3 MidnightColor = texture(Midnight, TexCoords).rgb;  
	vec3 Land2Color = texture(Land2, TexCoords).rgb;      
	vec3 Land1Color = texture(Land1, TexCoords).rgb;      
	vec3 TreesColor = texture(Trees, TexCoords).rgb;
	vec3 SkyColor = texture(Sky, TexCoords).rgb;    
	vec3 StarsColor = texture(Stars, TexCoords).rgb;


	//MidnightColor += StarsColor;
	//MidnightColor += SkyColor;
	//MidnightColor += TreesColor;
	//MidnightColor += Land1Color;
	//MidnightColor += Land2Color;

	FragColor = vec4(MidnightColor, 1.0);
}