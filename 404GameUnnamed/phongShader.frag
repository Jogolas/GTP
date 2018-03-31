#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light {
	vec4 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform Material material;
uniform Light light;

in vec3 Normal;
in vec3 FragPos;

in vec2 TexCoords;


void main()
{
	// Setting up Ambient Light
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	//"When calculating lighting we usually do not care about the magnitude of a vector or their position; we only care about their direction. 
	//Because we only care about their direction almost all the calculations are done with unit vectors since it simplifies most 
	//calculations (like the dot product). 
	//So when doing lighting calculations, make sure you always normalize the relevant vectors to ensure they're actual unit vectors. 
	//Forgetting to normalize a vector is a popular mistake." - JoeyDeVries, https://learnopengl.com/Lighting/Basic-Lighting

	// Setting up Diffuse Light
	vec3 norm = normalize(Normal);
	vec3 lightDir;
	if(light.position.w == 1.0) // if the w component exists, then we know the light is not directional
		lightDir = normalize(light.position.xyz - FragPos);
	else if(light.position.w == 0.0) // if the w component does not exist, then the light is directional.
		lightDir = normalize(-light.position.xyz);
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	// Setting up Specular Light
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	// setting up emission
	vec3 emission = texture(material.emission, TexCoords).rgb;

	// Setting Attenuation
	float distance;
	float attenuation = 1.0f;
	if(light.position.w == 1.0) { // check if point light
		distance = length(light.position.xyz - FragPos);
		attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	}

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;


	vec3 result = ambient + diffuse + specular + emission;
	FragColor = vec4(result, 1.0);
}