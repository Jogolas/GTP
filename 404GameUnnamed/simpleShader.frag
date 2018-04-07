#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
	vec4 color = texture(texture_diffuse1, TexCoords);

	if(color.rgb == 1.0) color.a = 0.0;

	if(color.a <= 0) discard;

    FragColor = color;
}