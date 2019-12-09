#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

// declare an interface block; see 'Advanced GLSL' for what these are.
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
	outData.FragPos = vec3(model[3][0], model[3][1], model[3][2]);
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
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 color = texture(texture_diffuse1, inData.TexCoords).rgb;
	// ambient
	vec3 ambient = 0.05 * color;

	// diffuse
	vec3 lightDir = normalize(lightPos - inData.FragPos);
	vec3 normal = normalize(inData.Normal);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * color;

	// specular
	vec3 viewDir = normalize(viewPos - inData.FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = 0.0;

	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

	vec3 specular = vec3(0.3) * spec; // assuming bright white light color
	FragColor = vec4(ambient + diffuse + specular, 1.0);
}