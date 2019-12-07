#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 ourColor;

uniform vec3 lightColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	ourColor = lightColor;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

in vec3 ourColor;

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0);
}