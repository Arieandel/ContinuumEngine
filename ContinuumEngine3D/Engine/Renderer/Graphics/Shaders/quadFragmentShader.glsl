#version 330 core
out vec4 FragColor;

in vec3 Position;
in vec2 TexCoords;


uniform sampler2D quadSample;

void main()
{             
  
    vec3 bloomColor = texture(quadSample, TexCoords).rgb;
    FragColor = vec4(bloomColor, 1.0);
}