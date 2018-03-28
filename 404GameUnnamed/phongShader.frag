#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D texture_diffuse1;

uniform Material material;
uniform Light light;

in vec3 Normal;
in vec3 FragPos;

in vec2 TexCoords;


void main()
{
	// Setting up Ambient Light
	vec3 ambient = light.ambient * material.ambient;
	
	//"When calculating lighting we usually do not care about the magnitude of a vector or their position; we only care about their direction. 
	//Because we only care about their direction almost all the calculations are done with unit vectors since it simplifies most 
	//calculations (like the dot product). 
	//So when doing lighting calculations, make sure you always normalize the relevant vectors to ensure they're actual unit vectors. 
	//Forgetting to normalize a vector is a popular mistake." - JoeyDeVries, https://learnopengl.com/Lighting/Basic-Lighting

	// Setting up Diffuse Light
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	// Setting up Specular Light
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);


	vec3 result = ambient + diffuse + specular;
	FragColor = texture(texture_diffuse1, TexCoords) * vec4(result, 1.0);
}