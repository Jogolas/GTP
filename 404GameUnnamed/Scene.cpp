#include "Scene.h"
#include "NPC.h"
#include "SDL_timer.h"
#include <iostream>


Scene::Scene(bool active)
{
	player = new Player(glm::vec3(10.0f, 0.0f, 5.0f));
	boss = new NPC(glm::vec3(0, 0, 0), glm::vec3(1.5f, 1.5f, 1.5f), 100.0f);

	glm::vec3 crateScale(6, 30, 6);

	ground = new Environment(glm::vec3(0, -2, 0), glm::vec3(75, 1, 75), 0, glm::vec3(0, 1, 0));
	wall[0] = new Environment(glm::vec3(75, 49, 0), glm::vec3(2, 50, 75), 0, glm::vec3(0, 1, 0));
	wall[1] = new Environment(glm::vec3(0, 49, 75), glm::vec3(75, 50, 2), 0, glm::vec3(0, 1, 0));
	wall[2] = new Environment(glm::vec3(-75, 49, 0), glm::vec3(2, 50, 75), 0, glm::vec3(0, 1, 0));
	wall[3] = new Environment(glm::vec3(0, 49, -75), glm::vec3(75, 50, 2), 0, glm::vec3(0, 1, 0));

	crates[0] = new Environment(glm::vec3(45, 29, 45), crateScale, 0, glm::vec3(0, 1, 0));
	crates[1] = new Environment(glm::vec3(45, 29, -45), crateScale, 0, glm::vec3(0, 1, 0));
	crates[2] = new Environment(glm::vec3(-45, 29, -45), crateScale, 0, glm::vec3(0, 1, 0));
	crates[3] = new Environment(glm::vec3(-45, 29, 45), crateScale, 0, glm::vec3(0, 1, 0));

	crates[4] = new Environment(glm::vec3(0, 29, -57), crateScale, 0, glm::vec3(0, 1, 0));
	crates[5] = new Environment(glm::vec3(0, 29, 57), crateScale, 0, glm::vec3(0, 1, 0));
	crates[6] = new Environment(glm::vec3(-57, 29, 0), crateScale, 0, glm::vec3(0, 1, 0));
	crates[7] = new Environment(glm::vec3(57, 29, 0), crateScale, 0, glm::vec3(0, 1, 0));

	lightingShader = Shader("phongShader.vert", "phongShader.frag");
	lampShader = Shader("simpleShader.vert", "simpleShader.frag");
	celShader = Shader("celShader.vert", "celShader.frag");

	bossObject = Model("models/BossModel.obj");
	cubeObject = Model("models/TexturedCube.obj");

	diffuseMap = Renderer::pngLoader("boxImage.png");
	specularMap = Renderer::pngLoader("boxImageSpecularMap.png");
	emissionMap = Renderer::pngLoader("boxImageEmission.png");

	groundDiffuse = Renderer::pngLoader("groundDiffuse.png");
	groundSpecular = Renderer::pngLoader("boxImageSpecularMap.png");
	groundEmission = Renderer::pngLoader("groundEmission.png");

	PlayerHUD = Renderer::pngLoader("HUDforProjectcopy.png");
	playerDiffuse = Renderer::pngLoader("PlayerDiffuse.png");
	playerSpecular = Renderer::pngLoader("PlayerSpecular.png");
	playerEmission = Renderer::pngLoader("PlayerEmission.png");

	bossDiffuse = Renderer::pngLoader("bossDiffuse.png");
	bossSpecular = Renderer::pngLoader("bossSpecular.png");
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

void Scene::setupMaterial(Shader shader, float shininess)
{
	// the integer value indicates the texture location
	// before appling the type of map to the object, first use the glActiveTexture() function for each type you wish to use
	// and then bind the active texture to the appropriate texture.
	// GLTEXTURE0 will map the diffuse
	// GLTEXTURE1 will map the specular (if any exist for the texture)
	// GLTEXTURE2 will map the emission (if any exist for the texture)
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);
	shader.setInt("material.emission", 2);
	shader.setFloat("material.shininess", shininess);
}

void Scene::setupLight(Shader shader, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	shader.setVec3("light.ambient", ambient);
	shader.setVec3("light.diffuse", diffuse);
	shader.setVec3("light.specular", specular);

	shader.setFloat("light.constant", 1.0);
	shader.setFloat("light.linear", 0.014);
	shader.setFloat("light.quadratic", 0.0007);
}

void Scene::useTexture(GLuint diffuse, GLuint specular, GLuint emission)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse);

	if (specular != NULL) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specular);
	}

	if (emission != NULL) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, emission);
	}
}

void Scene::drawScene()
{
	// view and projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(player->cam.Zoom), 800.0f / 600.0f, 1.0f, 500.0f);
	glm::mat4 view = player->cam.GetViewMatrix();

	celShader.use();

	setupMaterial(celShader, 32.0f);
	setupLight(celShader, glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));
	celShader.setVec4("light.position", lightPos);

	celShader.setMat4("projection", projection);
	celShader.setMat4("view", view);

	celShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.3f));

	useTexture(playerDiffuse, playerSpecular, playerEmission);

	//player
	glm::mat4 model = player->draw();
	celShader.setMat4("model", model);
	bossObject.DrawMesh(celShader);

	// be sure to activate shader when setting uniforms and drawing objects
	lightingShader.use();
	setupMaterial(lightingShader, 32.0f); // this only needs to be called if the material is different for each object.

	setupLight(lightingShader, glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));
	lightingShader.setVec4("light.position", lightPos);

	lightingShader.setVec3("viewPos", player->cam.Position);
	lightingShader.setMat4("projection", projection);
	lightingShader.setMat4("view", view);

	glBindTexture(GL_TEXTURE_2D, 0); //remember to unbind textures after you apply them, and before using a new texture.


	useTexture(bossDiffuse, bossSpecular, NULL);

	//boss
	if (boss != nullptr) {
		model = dynamic_cast<NPC*>(boss)->draw();
		lightingShader.setMat4("model", model);
		bossObject.DrawMesh(lightingShader);
	}

	glBindTexture(GL_TEXTURE_2D, 0); //remember to unbind textures after you apply them, and before using a new texture.


	useTexture(groundDiffuse, NULL, groundEmission);

	//ground
	model = ground->draw();
	lightingShader.setMat4("model", model);
	cubeObject.DrawMesh(lightingShader);

	glBindTexture(GL_TEXTURE_2D, 0); //remember to unbind textures after you apply them, and before using a new texture.


	useTexture(diffuseMap, specularMap, NULL);

	//walls
	for (int i = 0; i < 4; i++) {
		model = wall[i]->draw();
		lightingShader.setMat4("model", model);
		cubeObject.DrawMesh(lightingShader);
	}


	//crates
	for (int i = 0; i < 8; i++) {
		model = crates[i]->draw();
		lightingShader.setMat4("model", model);
		cubeObject.DrawMesh(lightingShader);
	}

	glBindTexture(GL_TEXTURE_2D, 0); //remember to unbind textures after you apply them, and before using a new texture.

	//light position
	lampShader.use();
	lampShader.setMat4("projection", projection);
	lampShader.setMat4("view", view);

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(lightPos));
	model = glm::scale(model, glm::vec3(0.2f));

	lampShader.setMat4("model", model);
	cubeObject.DrawMesh(lampShader);

	//boss spell
	if (dynamic_cast<NPC*>(boss)->getSpell() != nullptr) {
		model = dynamic_cast<NPC*>(boss)->getSpell()->draw();
		lampShader.setMat4("model", model);
		cubeObject.DrawMesh(lampShader);
	}



	// HUD ELEMENTS
	projection = glm::mat4(1.0); //reset projection matrix for HUD
	projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 1.0f, 150.0f);

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, PlayerHUD);

	projection = glm::translate(projection, glm::vec3(400.0f, 300.0f, 1.0f));
	projection = glm::scale(projection, glm::vec3(100.0f, 500.0f, 0.0f));
	projection = glm::rotate(projection, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	projection = glm::rotate(projection, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	lampShader.setMat4("model", projection);
	lampShader.setMat4("view", projection);
	cubeObject.DrawMesh(lampShader);

	glBindTexture(GL_TEXTURE_2D, 0); // remember to unbind textures
	//remember to turn on depth test.
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}


void Scene::collisions()
{
	cd.planeCollision(player->g_object.colObj, ground->getColObject());

	//player wall/box collisions
	for (int i = 0; i < 8; i++) {

		if (i < 4) cd.playerBoxCollision(player->g_object, wall[i]->getColObject());

		cd.playerBoxCollision(player->g_object, crates[i]->getColObject());
		player->g_object.position = player->g_object.colObj->getPosition();
		cd.npcBoxCollision(dynamic_cast<NPC*>(boss)->getColObject(), crates[i]->getColObject());
		boss->setPosition(dynamic_cast<NPC*>(boss)->getColObject()->getPosition());

		if (dynamic_cast<NPC*>(boss)->getSpell() != nullptr) {
			cd.AISpellBoxCollision(dynamic_cast<NPC*>(boss)->getSpell()->getColObj(), crates[i]->getColObject());
			dynamic_cast<NPC*>(boss)->getSpell()->setPosition(dynamic_cast<NPC*>(boss)->getSpell()->getColObj()->getPosition());
		}
	}

}


void Scene::updateScene()
{
	dynamic_cast<NPC*>(boss)->update(player);
	keyboard.handlePlayerkeyboard(player);
	player->update();
	mouse.MouseMotion(player);
	collisions();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_I]) lightPos.x += 0.1f;
	if (keys[SDL_SCANCODE_J]) lightPos.z += 0.1f;
	if (keys[SDL_SCANCODE_K]) lightPos.x -= 0.1f;
	if (keys[SDL_SCANCODE_L]) lightPos.z -= 0.1f;
	if (keys[SDL_SCANCODE_O]) lightPos.y += 0.1f;
	if (keys[SDL_SCANCODE_P]) lightPos.y -= 0.1f;
}