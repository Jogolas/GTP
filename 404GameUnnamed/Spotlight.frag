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

	float cutOff;
	float outerCutOff;
};

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;


void main()
{
	vec3 lightDir = normalize(light.position.xyz - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	if(theta > light.outerCutOff) {
		// Setting up Ambient Light
		vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

		// Setting up Diffuse Light
		vec3 norm = normalize(Normal);
	
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

		// Setting up Specular Light
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);

		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

		// Setting Attenuation
		float distance;
		float attenuation = 1.0f;
		if(light.position.w == 1.0) { // check if point light
			distance = length(light.position.xyz - FragPos);
			attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
		}

		diffuse *= intensity;
		specular *= intensity;

		// remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight.
		//diffuse *= attenuation;
		//specular *= attenuation;

		vec3 result = ambient + diffuse + specular;
		FragColor = vec4(result, 1.0);
	}
	else {
		FragColor = vec4((light.ambient * texture(material.diffuse, TexCoords).rgb), 1.0);
	}
}