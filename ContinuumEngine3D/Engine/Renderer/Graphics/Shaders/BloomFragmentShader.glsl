#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;


struct Light {
    vec3 Position;
    vec3 Color;
};

uniform Light lights[3];
uniform sampler2D diffuseTexture;
uniform vec3 viewPosition;

void main()
{           
    vec3 color = texture(diffuseTexture, TexCoords).rgb;
    vec3 normal = normalize(Normal);
    // ambient
    vec3 ambient = 0.0 * color;
    // lighting
    vec3 lighting = vec3(0.0);
    vec3 viewDir = normalize(viewPosition - FragPosition);
    for(int i = 0; i < 3; i++)
    {
        // diffuse
        vec3 lightDir = normalize(lights[i].Position - FragPosition);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 result = lights[i].Color * diff * color;      
        // attenuation (use quadratic as we have gamma correction)
        float distance = length(FragPosition - lights[i].Position);
        result *= 1.0 / (distance * distance);
        lighting += result;

                
    }
    vec3 result = ambient + lighting * 10.0;
    // check whether result is higher than some threshold, if so, output as bloom threshold color
    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    FragColor = vec4(result, 1.0);
}