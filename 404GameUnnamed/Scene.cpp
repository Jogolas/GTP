#include "Scene.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#define DEG_TO_RADIAN 0.017453293

Renderer::lightStruct light = {
	{ 0.3f, 0.3f, 0.3f, 1.0f }, // ambient
	{ 1.0f, 1.0f, 1.0f, 1.0f }, // diffuse
	{ 1.0f, 1.0f, 1.0f, 1.0f }, // specular
	{ 10.0f, 10.0f, 10.0f, 1.0f }  // position
};


Renderer::materialStruct material = {
	{ 0.4f, 0.4f, 0.4f, 1.0f }, // ambient
	{ 0.4f, 0.4f, 0.4f, 1.0f }, // diffuse
	{ 0.2f, 0.2f, 0.2f, 1.0f }, // specular
	2.0f  // shininess
};

Renderer::materialStruct tMaterial = {
	{ 0.2f, 0.2f, 0.2f, 1.0f }, // ambient
	{ 0.5f, 0.5f, 0.5f, 1.0f }, // diffuse
	{ 0.5f, 0.5f, 0.5f, 1.0f }, // specular
	2.0f  // shininess
};

glm::vec4 lightPos(0.0f, 10.0f, 0.0f, 1.0f); //light position

GLfloat attConstant = 0.05f;
GLfloat attLinear = 0.0f;
GLfloat attQuadratic = 0.0f;
GLuint texture[1];

Scene::Scene()
{
	//player = new Player();
	cam = new Camera();
	ground = new Environment(glm::vec3(0, -1, 0), glm::vec3(50.0, 0.5, 50.0), 0, glm::vec3(0, 1, 0));

	////phong tex shader program
	program[0] = shader->createShader("phong-tex.vert", "phong-tex.frag", tMaterial, light);
	shader->setAttenuation(program[1], attConstant, attLinear, attQuadratic);

	////skybox program
	skyProgram = Renderer::initiliaseShader("cubeMap.vert", "cubeMap.frag");

	const char *cubeTexFiles[6] = {
		"cloudy-skybox/back.bmp",
		"cloudy-skybox/front.bmp",
		"cloudy-skybox/right.bmp",
		"cloudy-skybox/left.bmp",
		"cloudy-skybox/up.bmp",
		"cloudy-skybox/down.bmp"
	};
	loadCubeMap(cubeTexFiles, &skybox[0]);
}

GLuint Scene::loadCubeMap(const char *fname[6], GLuint *texID)
{
	glGenTextures(1, texID); // generate texture ID
	GLenum sides[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y };
	SDL_Surface *tmpSurface;

	glBindTexture(GL_TEXTURE_CUBE_MAP, *texID); // bind texture and set parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	GLuint externalFormat;
	for (int i = 0; i < 6; i++)
	{
		// load file - using core SDL library
		tmpSurface = SDL_LoadBMP(fname[i]);
		if (!tmpSurface)
		{
			std::cout << "Error loading bitmap" << std::endl;
			return *texID;
		}

		// skybox textures should not have alpha (assuming this is true!)
		SDL_PixelFormat *format = tmpSurface->format;
		externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;

		glTexImage2D(sides[i], 0, GL_RGB, tmpSurface->w, tmpSurface->h, 0,
			externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
		// texture loaded, free the temporary buffer
		SDL_FreeSurface(tmpSurface);
	}
	return *texID;	// return value of texure ID, redundant really
}


void Scene::drawScene()
{
	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f * DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 300.0f);


	glm::mat4 modelview(1.0);

	mvStack.push(modelview);
	mvStack.top() = cam->draw(mvStack.top(), dynamic_cast<Player*>(player));

	// skybox as single cube using cube map
	glCullFace(GL_FRONT);
	glUseProgram(skyProgram);
	Renderer::setMatrix(skyProgram, "projection", glm::value_ptr(projection));
	glDepthMask(GL_FALSE); // make sure writing to update depth test is off
	glm::mat3 mvRotOnlyMat3 = glm::mat3(mvStack.top());
	mvStack.push(glm::mat4(mvRotOnlyMat3));

	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox[0]);
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(1.5f, 1.5f, 1.5f));
	Renderer::setMatrix(skyProgram, "modelview", glm::value_ptr(mvStack.top()));
	meshes[0].drawMesh(meshes[0].getMeshID());
	mvStack.pop();
	glCullFace(GL_BACK);


	// back to remainder of rendering
	glDepthMask(GL_TRUE); // make sure depth test is on

	glm::vec4 tmp = mvStack.top() * lightPos;
	light.position[0] = tmp.x;
	light.position[1] = tmp.y;
	light.position[2] = tmp.z;

	shader->unbindShaderProgram();
	mvStack.pop(); //initial matrix
}

void Scene::updateScene()
{
	player->update(10);

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_I]) lightPos.z -= 0.2f;
	if (keys[SDL_SCANCODE_J]) lightPos.x -= 0.2f;
	if (keys[SDL_SCANCODE_K]) lightPos.z += 0.2f;
	if (keys[SDL_SCANCODE_L]) lightPos.x += 0.2f;
	if (keys[SDL_SCANCODE_U]) lightPos.y += 0.2f;
	if (keys[SDL_SCANCODE_H]) lightPos.y -= 0.2f;
	if (keys[SDL_SCANCODE_E]) lightPos = glm::vec4(0.0f, 10.0f, 0.0f, 1.0f);
}