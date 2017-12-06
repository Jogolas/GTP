#include "Scene.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "NPC.h"

#define DEG_TO_RADIAN 0.017453293

Renderer::lightStruct light = {
	{ 0.4f, 0.4f, 0.4f, 1.0f }, // ambient
	{ 1.0f, 1.0f, 1.0f, 1.0f }, // diffuse
	{ 1.0f, 1.0f, 1.0f, 1.0f }, // specular
	{ 10.0f, 10.0f, 10.0f, 1.0f }  // position
};


Renderer::materialStruct tmaterial = {
	{ 0.4f, 0.4f, 0.4f, 1.0f }, // ambient
	{ 0.4f, 0.4f, 0.4f, 1.0f }, // diffuse
	{ 0.2f, 0.2f, 0.2f, 1.0f }, // specular
	2.0f  // shininess
};

Renderer::materialStruct material = {
	{ 0.4f, 0.4f, 0.4f, 1.0f }, // ambient
	{ 0.8f, 0.8f, 0.8f, 1.0f }, // diffuse
	{ 0.8f, 0.8f, 0.8f, 1.0f }, // specular
	1.0f  // shininess
};

glm::vec4 lightPos(0.0f, 10.0f, 0.0f, 1.0f); //light position

GLfloat attConstant = 1.0f;
GLfloat attLinear = 0.0f;
GLfloat attQuadratic = 0.0f;
GLuint texture[4];

Scene::Scene()
{
	player = new Player(glm::vec3(5, 0, 8));
	boss = new NPC();
	cam = new Camera();
	ground = new Environment(glm::vec3(0, -1, 0), glm::vec3(50.0, 0.5, 50.0), 0, glm::vec3(0, 1, 0));
	shader = new Shader();

	wall[0] = new Environment(glm::vec3(50, 10, 0), glm::vec3(2, 50, 50), 0, glm::vec3(0, 1, 0));
	wall[1] = new Environment(glm::vec3(0, 10, 50), glm::vec3(50, 50, 2), 0, glm::vec3(0, 1, 0));
	wall[2] = new Environment(glm::vec3(-50, 10, 0), glm::vec3(2, 50, 50), 0, glm::vec3(0, 1, 0));
	wall[3] = new Environment(glm::vec3(0, 10, -50), glm::vec3(50, 50, 2), 0, glm::vec3(0, 1, 0));

	program[0] = shader->createShader("phong-tex.vert", "phong-tex.frag", material, light);
	shader->setAttenuation(program[0], attConstant, attLinear, attQuadratic);

	////toon tex shader program
	program[1] = shader->createShader("toonReflection.vert", "toonReflection.frag", material, light);
	shader->setAttenuation(program[0], attConstant, attLinear, attQuadratic);
	GLuint uniformIndex = glGetUniformLocation(program[1], "textureUnit1");
	glUniform1i(uniformIndex, 1);
	uniformIndex = glGetUniformLocation(program[1], "textureUnit0");
	glUniform1i(uniformIndex, 0);
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

	texture[0] = Renderer::bitMapLoader("sky.bmp");
	texture[1] = Renderer::bitMapLoader("studdedmetal.bmp");
	texture[2] = Renderer::bitMapLoader("boxTexture.bmp");
	texture[3] = Renderer::bitMapLoader("ball.bmp");

	meshes[0].createMesh(meshID[0], "BossModel.obj");
	meshes[1].createMesh(meshID[1], "cube.obj");
	//meshes[2].createMesh(meshID[2], "HeroMan.obj");
	meshes[3].createMesh(meshID[3], "bossAbility.obj");

	boss->setMesh(meshes[0]);
	ground->setMesh(meshes[1]);
	player->setMesh(meshes[2]);

	for (GLuint i = 0; i < 4; i++) wall[i]->setMesh(meshes[1]);
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
	meshes[0].drawMesh(meshes[1].getMeshID());
	mvStack.pop();
	glCullFace(GL_BACK);


	// back to remainder of rendering
	glDepthMask(GL_TRUE); // make sure depth test is on

	glm::vec4 tmp = mvStack.top() * lightPos;
	light.position[0] = tmp.x;
	light.position[1] = tmp.y;
	light.position[2] = tmp.z;



	shader->bindShaderProgram(program[0]);
	shader->useMatrix4fv(projection, "projection");
	Renderer::setLightPos(program[0], glm::value_ptr(tmp));

	////ground
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glm::mat4 modelMatrix(1.0);
	mvStack.push(mvStack.top());
	modelMatrix = ground->draw(modelMatrix);
	mvStack.top() *= modelMatrix;
	shader->useMatrix4fv(mvStack.top(), "modelview");
	ground->getMesh().drawMesh(ground->getMesh().getMeshID());
	mvStack.pop();

	//// walls
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	for (GLuint i = 0; i < 4; i++) {

		modelMatrix = glm::mat4(1.0); //reset modelmatrix
		mvStack.push(mvStack.top());
		modelMatrix = wall[i]->draw(modelMatrix);
		mvStack.top() *= modelMatrix;
		shader->useMatrix4fv(mvStack.top(), "modelview");
		wall[i]->getMesh().drawMesh(wall[i]->getMesh().getMeshID());
		mvStack.pop();
	}

	shader->unbindShaderProgram();


	shader->bindShaderProgram(program[1]);
	shader->useMatrix4fv(projection, "projection");
	Renderer::setLightPos(program[1], glm::value_ptr(tmp));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox[0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	////player
	mvStack.push(mvStack.top());
	modelMatrix = glm::mat4(1.0); //reset model matrix
	modelMatrix = player->draw(modelMatrix);
	mvStack.top() *= modelMatrix;
	shader->useMatrix4fv(mvStack.top(), "modelview");
	shader->useMatrix4fv(modelMatrix, "modelMatrix");
	GLuint uniformIndex = glGetUniformLocation(program[1], "cameraPos");
	glUniform3fv(uniformIndex, 1, glm::value_ptr(dynamic_cast<Player*>(player)->getEye()));
	Renderer::setMaterial(program[1], material);
	player->getMesh().drawMesh(player->getMesh().getMeshID());
	mvStack.pop();


	glBindTexture(GL_TEXTURE_2D, texture[1]);
	////boss
	mvStack.push(mvStack.top());
	modelMatrix = glm::mat4(1.0); //reset model matrix
	modelMatrix = boss->draw(modelMatrix);
	mvStack.top() *= modelMatrix;
	shader->useMatrix4fv(mvStack.top(), "modelview");
	shader->useMatrix4fv(modelMatrix, "modelMatrix");
	uniformIndex = glGetUniformLocation(program[1], "cameraPos");
	glUniform3fv(uniformIndex, 1, glm::value_ptr(dynamic_cast<Player*>(player)->getEye()));
	Renderer::setMaterial(program[1], material);
	boss->getMesh().drawMesh(boss->getMesh().getMeshID());
	mvStack.pop();

	if (dynamic_cast<NPC*>(boss)->getSpell() != nullptr) {
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		mvStack.push(mvStack.top());
		modelMatrix = glm::mat4(1.0); //reset model matrix
		modelMatrix = glm::translate(modelMatrix, dynamic_cast<NPC*>(boss)->getSpell()->getPosition());
		mvStack.top() = glm::scale(mvStack.top(), glm::vec3(0.25f, 0.25f, 0.25f));
		mvStack.top() *= modelMatrix;
		shader->useMatrix4fv(mvStack.top(), "modelview");
		shader->useMatrix4fv(modelMatrix, "modelMatrix");
		uniformIndex = glGetUniformLocation(program[1], "cameraPos");
		glUniform3fv(uniformIndex, 1, glm::value_ptr(dynamic_cast<Player*>(player)->getEye()));
		Renderer::setMaterial(program[1], material);
		meshes[3].drawMesh(meshes[3].getMeshID());
		mvStack.pop();
	}

	shader->unbindShaderProgram();


	mvStack.pop(); //initial matrix
}

void Scene::updateScene()
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_1])
		dynamic_cast<NPC*>(boss)->getController()->setTarget(player->getGameObject());

	dynamic_cast<Player*>(player)->update();
	dynamic_cast<NPC*>(boss)->update();


}