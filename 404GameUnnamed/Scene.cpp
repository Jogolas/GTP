#include "Scene.h"
#include "NPC.h"
#include "SDL_timer.h"

#include <iostream>

#define DEG_TO_RADIAN 0.017453293

Scene::Scene(bool active)
{
	player = new Player(glm::vec3(0.0f, 0.0f, 5.0f));
	ground = new Environment(glm::vec3(0, -2, 0), glm::vec3(75, 1, 75), 0, glm::vec3(0, 1, 0));
	wall[0] = new Environment(glm::vec3(75, 74, 0), glm::vec3(2, 75, 75), 0, glm::vec3(0, 1, 0));
	wall[1] = new Environment(glm::vec3(0, 74, 75), glm::vec3(75, 75, 2), 0, glm::vec3(0, 1, 0));
	wall[2] = new Environment(glm::vec3(-75, 74, 0), glm::vec3(2, 75, 75), 0, glm::vec3(0, 1, 0));
	wall[3] = new Environment(glm::vec3(0, 74, -75), glm::vec3(75, 75, 2), 0, glm::vec3(0, 1, 0));

	crates[0] = new Environment(glm::vec3(45, 2, 45), glm::vec3(12, 3, 12), 0, glm::vec3(0, 1, 0));
	crates[1] = new Environment(glm::vec3(45, 2, -45), glm::vec3(12, 3, 12), 0, glm::vec3(0, 1, 0));
	crates[2] = new Environment(glm::vec3(-45, 2, -45), glm::vec3(12, 3, 12), 0, glm::vec3(0, 1, 0));
	crates[3] = new Environment(glm::vec3(-45, 2, 45), glm::vec3(12, 3, 12), 0, glm::vec3(0, 1, 0));

	crates[4] = new Environment(glm::vec3(0, 2, -36), glm::vec3(12, 3, 12), 0, glm::vec3(0, 1, 0));
	crates[5] = new Environment(glm::vec3(0, 2, 36), glm::vec3(12, 3, 12), 0, glm::vec3(0, 1, 0));
	crates[6] = new Environment(glm::vec3(-36, 2, 0), glm::vec3(12, 3, 12), 0, glm::vec3(0, 1, 0));
	crates[7] = new Environment(glm::vec3(36, 2, 0), glm::vec3(12, 3, 12), 0, glm::vec3(0, 1, 0));

	lightingShader = Shader("phongShader.vert", "phongShader.frag");
	lampShader = Shader("simpleShader.vert", "simpleShader.frag");

	bossObject = Model("models/BossModel.obj");
	cubeObject = Model("models/TexturedCube.obj");

	texture = Renderer::pngLoader("boxTexture.png");
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

GLfloat rotation = 0.0f;

void Scene::drawScene()
{
	// be sure to activate shader when setting uniforms and drawing objects
	lightingShader.use();
	lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("lightPos", lightPos);
	lightingShader.setVec3("viewPos", player->cam.Position);

	// view and projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(player->cam.Zoom), 800.0f / 600.0f, 1.0f, 500.0f);
	glm::mat4 view = player->cam.GetViewMatrix();

	lightingShader.setMat4("projection", projection);
	lightingShader.setMat4("view", view);

	// world transformations
	glm::mat4 model = player->draw();

	lightingShader.setMat4("model", model);
	bossObject.DrawMesh(lightingShader);


	//ground

	lightingShader.setVec3("objectColor", 0.5f, 0.5f, 0.5f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	model = glm::mat4(1.0); // reset model matrix
	model = ground->draw();

	lightingShader.setMat4("model", model);
	cubeObject.DrawMesh(lightingShader);


	//walls
	lightingShader.setVec3("objectColor", 1.0f, 0.5f, 1.0f);

	for (int i = 0; i < 4; i++) {
		model = glm::mat4(1.0); // reset model matrix
		model = wall[i]->draw();
		lightingShader.setMat4("model", model);
		cubeObject.DrawMesh(lightingShader);
	}

	lightingShader.setVec3("objectColor", 0.5f, 1.0f, 1.0f);

	for (int i = 0; i < 8; i++) {
		model = glm::mat4(1.0); // reset model matrix
		model = crates[i]->draw();
		lightingShader.setMat4("model", model);
		cubeObject.DrawMesh(lightingShader);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}


void Scene::collisions()
{
	cd.planeCollision(player->getColObject(), ground->getColObject());

	//player wall/box collisions
	for (int i = 0; i < 8; i++) {

		if (i < 4) cd.playerBoxCollision(player->getColObject(), wall[i]->getColObject());

		cd.playerBoxCollision(player->getColObject(), crates[i]->getColObject());
		player->setPosition(player->getColObject()->getPosition());
	}
}

void Scene::updateScene()
{
	player->update();
	collisions();
	mouse.MouseMotion(player);
}