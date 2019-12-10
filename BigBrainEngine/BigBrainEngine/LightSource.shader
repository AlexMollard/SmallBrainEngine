#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out Data{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
} outData;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	outData.FragPos = aPos;
	outData.Normal = aNormal;
	outData.TexCoords = aTexCoords;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment
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