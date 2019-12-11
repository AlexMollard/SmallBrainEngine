#version 330 core
out vec4 FragColor;

in Data{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} inData;

uniform sampler2D texture_diffuse1;

void main()
{
	vec3 color = texture(texture_diffuse1, inData.TexCoords).rgb;

	FragColor = vec4(color, 1.0);
}