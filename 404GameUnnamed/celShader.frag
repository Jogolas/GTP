#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

#define NR_POINT_LIGHTS 4

uniform vec3 objectColor;
uniform vec3 viewPos;

uniform Material material;
uniform DirLight dLight;
uniform PointLight pLights[NR_POINT_LIGHTS];

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
in vec3 ex_V;

// functions
vec4 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main()
{
	// define an output color value
	vec4 output = vec4(vec3(0.0), 1.0);

	// properties
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	// add the directional light's contribution to the ouput first
	output += calcDirLight(dLight, norm, viewDir);

	// then add point lights
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
		output += calcPointLight(pLights[i], norm, FragPos, viewDir);

	// setting up emission
	vec3 emission = texture(material.emission, TexCoords).rgb;


	FragColor.rgb = output.rgb + emission;
	FragColor.a = output.a;
}

vec4 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	// diffuse shading 
	float diff = max(dot(normal, lightDir), 0.0);

	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// combine results.
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	return vec4((ambient + diffuse + specular), 1.0);
}

vec4 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);

	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// attenuation
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	//ambient *= attenuation;
	diffuse *= attenuation;
    specular *= attenuation;

	vec4 tempColor = vec4(vec3(diffuse + specular), 1.0);
	vec4 litColor = tempColor;
	vec4 amb = min(vec4(ambient.rgb, 1.0), vec4(1.0f));

	litColor = min(litColor + amb, vec4(objectColor, 1.0));
	vec4 shade1 = smoothstep(vec4(0.2f), vec4(0.21f), litColor);
	vec4 shade2 = smoothstep(vec4(0.4f), vec4(0.41f), litColor);
	vec4 shade3 = smoothstep(vec4(0.8f), vec4(0.81f), litColor);

	// cel metallic shade
	float metallic = dot(normal, ex_V);
	metallic = smoothstep(0.4, 0.6, metallic);
	metallic = metallic / 2 + 1.0;

	vec4 colorA = max(max(0.3 * shade1, 0.5 * shade2), shade3);

	if(abs(dot(normal, ex_V)) < 0.25)
	{
		colorA = vec4(vec3(0.0), 1.0) * metallic;
	}

	return vec4((ambient + diffuse + specular), 1.0) * colorA;
}