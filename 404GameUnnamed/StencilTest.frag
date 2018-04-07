#version 330

out vec4 FragColor;

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0; // back to NDC
	return (2.0 * near * far) / (z * (far - near) - (far + near));
}

void main()
{

	// depth testing
	float depth = LinearizeDepth(gl_FragCoord.z);
	//float grey = (near + depth) / (near - far);

	//FragColor = vec4(vec3(grey), 1.0);

	FragColor = vec4(vec3(0.0), 1.0);
}