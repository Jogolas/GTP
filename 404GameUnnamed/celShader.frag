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
in vec3 ex_V;

in vec2 TexCoords;


void main()
{
	// Setting up Ambient Light
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

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


	// cel shader
	vec4 tempColor = vec4(vec3(diffuse + specular), 1.0);
	vec4 litColor = tempColor;
	vec4 amb = min(vec4(ambient.rgb, 1.0), vec4(1.0f));

	litColor = min(litColor + amb, vec4(objectColor, 1.0));
	vec4 shade1 = smoothstep(vec4(0.2f), vec4(0.21f), litColor);
	vec4 shade2 = smoothstep(vec4(0.4f), vec4(0.41f), litColor);
	vec4 shade3 = smoothstep(vec4(0.8f), vec4(0.81f), litColor);

	// cel metallic shade
	float metallic = dot(norm, ex_V);
	metallic = smoothstep(0.4, 0.6, metallic);
	metallic = metallic / 2 + 1.0;

	vec4 colorA = max(max(0.3 * shade1, 0.5 * shade2), shade3);

	if(abs(dot(norm, ex_V)) < 0.25)
	{
		colorA = vec4(vec3(0.0), 1.0) * metallic;
	}


	vec4 result = (colorA * metallic) + vec4(emission, 1.0);

	FragColor = result;
}