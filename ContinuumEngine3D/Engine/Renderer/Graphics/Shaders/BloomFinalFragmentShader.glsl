#version 330 core
out vec4 FragColor;

in vec3 Position;
in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform sampler2D Midnight;


//uniform samplerCube skybox;
uniform bool bloom;
uniform float exposure;

void main()
{           
	//vec3 skyboxColor = texture(skybox, Position).rgb;
    const float gamma = 2.2;
    vec3 hdrColor = texture(scene, TexCoords).rgb;      
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
	vec3 MidnightColor = texture(Midnight, TexCoords).rgb;  
	vec3 temp;


	temp = hdrColor;


	if(temp == vec3(0.0, 0.0, 0.0)){
		hdrColor += bloomColor;
	}



    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
	result = pow(result, vec3(1.0 / gamma));

	if(temp == vec3(0.0, 0.0, 0.0)){
	result += MidnightColor;
	}

    FragColor = vec4(result, 1.0);
}