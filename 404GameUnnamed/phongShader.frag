#version 330 core

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

void main()
{
	// Setting up Ambient Light
	float ambStr = 0.1;
	vec3 ambient = ambStr * lightColor;
	
	//"When calculating lighting we usually do not care about the magnitude of a vector or their position; we only care about their direction. 
	//Because we only care about their direction almost all the calculations are done with unit vectors since it simplifies most 
	//calculations (like the dot product). 
	//So when doing lighting calculations, make sure you always normalize the relevant vectors to ensure they're actual unit vectors. 
	//Forgetting to normalize a vector is a popular mistake." - JoeyDeVries, https://learnopengl.com/Lighting/Basic-Lighting

	// Setting up Diffuse Light
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// Setting up Specular Light
	float specStr = 0.5;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specStr * spec * lightColor;


	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0);
}