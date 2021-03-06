#include "Scene.h"
#include "NPC.h"
#include "SDL_timer.h"
#include <iostream>


Scene::Scene(bool active)
{
	player = new Player(glm::vec3(10.0f, 0.0f, 5.0f));
	boss = new NPC(glm::vec3(0, 0, 0), glm::vec3(1.5f, 1.5f, 1.5f), 10000.0f);

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
	outlineShader = Shader("StencilTest.vert", "StencilTest.frag");

	bossObject = Model("models/BossModel.obj");
	cubeObject = Model("models/TexturedCube.obj");

	wallDiffuse = Renderer::pngLoader("Textures/Environment/stoneTexture.png");

	crateDiffuse = Renderer::pngLoader("Textures/Environment/boxImage.png");
	crateSpecular = Renderer::pngLoader("Textures/Environment/boxImageSpecularMap.png");

	groundDiffuse = Renderer::pngLoader("Textures/Environment/groundDiffuse.png");
	groundSpecular = Renderer::pngLoader("Textures/Environment/groundSpecular.png");
	groundEmission = Renderer::pngLoader("Textures/Environment/groundEmission.png");

	windowTexture = Renderer::pngLoader("Textures/Environment/blending_transparent_window.png");

	PlayerHUD = Renderer::pngLoader("Textures/Player/playerHUDtwo.png");
	PlayerHUDHealth = Renderer::pngLoader("Textures/Player/PlayerHUDHealth.png");
	PlayerWin = Renderer::pngLoader("Textures/Player/winHud.png");
	PlayerLose = Renderer::pngLoader("Textures/Player/gameOverHud.png");

	fireHUD = Renderer::pngLoader("Textures/Player/fireIcon.png");
	iceHUD = Renderer::pngLoader("Textures/Player/iceIcon.png");
	elecHUD = Renderer::pngLoader("Textures/Player/elecIcon.png");

	playerDiffuse = Renderer::pngLoader("Textures/Player/PlayerDiffuse.png");
	playerSpecular = Renderer::pngLoader("Textures/Player/PlayerSpecular.png");
	playerEmission = Renderer::pngLoader("Textures/Player/PlayerEmission.png");

	bossDiffuse = Renderer::pngLoader("Textures/Boss/bossDiffuse.png");
	bossSpecular = Renderer::pngLoader("Textures/Boss/bossSpecular.png");
	bossEmission = Renderer::pngLoader("Textures/Boss/bossEmission.png");

	bossBar = Renderer::pngLoader("Textures/Boss/bossHealthBar.png");
	bossHealth = Renderer::pngLoader("Textures/Boss/bossHealthDisplay.png");
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

// should really read from a file rather than hard code this.
void Scene::setupPointLight(Shader shader, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	// postions
	shader.setVec3("pLights[0].position", pointLightPositions[0]);
	shader.setVec3("pLights[1].position", pointLightPositions[1]);
	shader.setVec3("pLights[2].position", pointLightPositions[2]);
	shader.setVec3("pLights[3].position", pointLightPositions[3]);

	// light values
	shader.setVec3("pLights[0].ambient", ambient);
	shader.setVec3("pLights[0].diffuse", diffuse);
	shader.setVec3("pLights[0].specular", specular);

	shader.setVec3("pLights[1].ambient", ambient);
	shader.setVec3("pLights[1].diffuse", diffuse);
	shader.setVec3("pLights[1].specular", specular);

	shader.setVec3("pLights[2].ambient", ambient);
	shader.setVec3("pLights[2].diffuse", diffuse);
	shader.setVec3("pLights[2].specular", specular);

	shader.setVec3("pLights[3].ambient", ambient);
	shader.setVec3("pLights[3].diffuse", diffuse);
	shader.setVec3("pLights[3].specular", specular);

	// attenuation values
	shader.setFloat("pLights[0].constant", 1.0);
	shader.setFloat("pLights[0].linear", 0.07);
	shader.setFloat("pLights[0].quadratic", 0.017);

	shader.setFloat("pLights[1].constant", 1.0);
	shader.setFloat("pLights[1].linear", 0.07);
	shader.setFloat("pLights[1].quadratic", 0.017);

	shader.setFloat("pLights[2].constant", 1.0);
	shader.setFloat("pLights[2].linear", 0.07);
	shader.setFloat("pLights[2].quadratic", 0.017);

	shader.setFloat("pLights[3].constant", 1.0);
	shader.setFloat("pLights[3].linear", 0.07);
	shader.setFloat("pLights[3].quadratic", 0.017);
}

void Scene::setupDirLight(Shader shader, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	shader.setVec3("dLight.direction", dirLightPosition);
	shader.setVec3("dLight.ambient", ambient);
	shader.setVec3("dLight.diffuse", diffuse);
	shader.setVec3("dLight.specular", specular);
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

void Scene::unbindTextures()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Scene::drawScene()
{

	// view and projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(player->cam.Zoom), 1280.0f / 720.0f, 1.0f, 500.0f);
	glm::mat4 view = player->cam.GetViewMatrix();
	glm::mat4 model;

	for (int pass = 0; pass < 2; pass++) {

		if (pass == 0) { // first pass

			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);


			celShader.use();
			setupMaterial(celShader, 32.0f);
			setupDirLight(celShader, glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));
			setupPointLight(celShader, glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));
			celShader.setMat4("projection", projection);
			celShader.setMat4("view", view);
			celShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.3f));


			//player
			useTexture(playerDiffuse, playerSpecular, playerEmission);
			model = player->draw();
			celShader.setMat4("model", model);
			bossObject.DrawMesh(celShader);
			unbindTextures(); //remember to unbind textures after you apply them, and before using a new texture.

			glStencilMask(0x00);

			//boss
			useTexture(bossDiffuse, bossSpecular, bossEmission);
			if (boss != nullptr) {
				model = dynamic_cast<NPC*>(boss)->draw();
				celShader.setMat4("model", model);
				bossObject.DrawMesh(celShader);
			}
			unbindTextures(); //remember to unbind textures after you apply them, and before using a new texture.



			// be sure to activate shader when setting uniforms and drawing objects
			lightingShader.use();
			setupMaterial(lightingShader, 32.0f); // this only needs to be called if the material is different for each object.

			setupDirLight(lightingShader, glm::vec3(0.05f), glm::vec3(0.5f), glm::vec3(1.0f));
			setupPointLight(lightingShader, glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));

			lightingShader.setVec3("viewPos", player->cam.Position);
			lightingShader.setMat4("projection", projection);
			lightingShader.setMat4("view", view);


			//ground
			useTexture(groundDiffuse, groundSpecular, groundEmission);
			model = ground->draw();
			lightingShader.setMat4("model", model);
			cubeObject.DrawMesh(lightingShader);

			unbindTextures(); //remember to unbind textures after you apply them, and before using a new texture.


			//walls
			useTexture(wallDiffuse, NULL, NULL);
			for (int i = 0; i < 4; i++) {
				model = wall[i]->draw();
				lightingShader.setMat4("model", model);
				cubeObject.DrawMesh(lightingShader);
			}
			unbindTextures();


			useTexture(crateDiffuse, crateSpecular, NULL);
			//crates
			for (int i = 0; i < 8; i++) {
				model = crates[i]->draw();
				lightingShader.setMat4("model", model);
				cubeObject.DrawMesh(lightingShader);
			}

			unbindTextures(); //remember to unbind textures after you apply them, and before using a new texture.


			//light position
			lampShader.use();
			lampShader.setMat4("projection", projection);
			lampShader.setMat4("view", view);
			lampShader.setVec3("objectColor", glm::vec3(1.0, 1.0, 1.0));

			useTexture(windowTexture, NULL, NULL);

			for (int i = 0; i < 4; i++) {
				model = glm::mat4(1.0);
				model = glm::translate(model, pointLightPositions[i]);
				model = glm::scale(model, glm::vec3(0.2f));

				lampShader.setMat4("model", model);
				cubeObject.DrawMesh(lampShader);
			}


			//boss spell
			for (int i = 0; i < 3; i++)
				if (dynamic_cast<NPC*>(boss)->getSpell(i) != nullptr) {
					model = dynamic_cast<NPC*>(boss)->getSpell(i)->draw();
					lampShader.setMat4("model", model);
					cubeObject.DrawMesh(lampShader);
				}

			for (int i = 0; i < 3; i++) {
				model = player->spells[i]->draw();
				lampShader.setMat4("model", model);
				cubeObject.DrawMesh(lampShader);
			}


			//HUD ELEMENTS
			glDisable(GL_DEPTH_TEST);
			if (playing) //display hud while playing
			{
				useTexture(PlayerHUD, NULL, NULL);
			}
			else if (isWon) //display win hud
			{
				useTexture(PlayerWin, NULL, NULL);
			}
			else if (isLost) //displays game over hud
			{
				useTexture(PlayerLose, NULL, NULL);
			}

			lampShader.setVec3("objectColor", glm::vec3(1.0, 1.0, 1.0));
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 0, 1));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.0f));
			lampShader.setMat4("projection", glm::mat4(1.0));
			lampShader.setMat4("model", model);
			lampShader.setMat4("view", glm::mat4(1.0));
			cubeObject.DrawMesh(lampShader);

			unbindTextures(); //remember to unbind textures after you apply them, and before using a new texture.


			//getting the health percentage for the HUD
			float ph = (player->getHealth() / 1000.0f);

			useTexture(PlayerHUDHealth, NULL, NULL);
			lampShader.setVec3("objectColor", glm::vec3(0.0f + (1 - ph), 1.0f * ph, 0.0f));
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.2975f, 0.725f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model = glm::scale(model, glm::vec3(0.15f * (ph), 0.265f * (ph), 0.0f));
			lampShader.setMat4("projection", glm::mat4(1.0));
			lampShader.setMat4("model", model);
			lampShader.setMat4("view", glm::mat4(1.0));
			
			if (playing) //display icon while playing
			{
				cubeObject.DrawMesh(lampShader);
			}

			float bhp = (dynamic_cast<NPC*>(boss)->getHealth() / 10000.0f);

			//BOSS HEALTH BAR
			useTexture(bossBar, NULL, NULL);
			lampShader.setVec3("objectColor", glm::vec3(1.0f));
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f, -0.9f, 0.0f));
			//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model = glm::scale(model, glm::vec3(0.5f, 0.05f, 1.0f));
			lampShader.setMat4("projection", glm::mat4(1.0));
			lampShader.setMat4("model", model);
			lampShader.setMat4("view", glm::mat4(1.0));

			if (playing) //display icon while playing
			{
				cubeObject.DrawMesh(lampShader);
			}

			//BOSS HEALTH DISPLAY
			useTexture(bossHealth, NULL, NULL);
			lampShader.setVec3("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f, -0.9f, 0.0f));
			//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1, 0, 0));
			model = glm::scale(model, glm::vec3(0.475f * bhp, 0.035f, 1.0f));
			lampShader.setMat4("projection", glm::mat4(1.0));
			lampShader.setMat4("model", model);
			lampShader.setMat4("view", glm::mat4(1.0));
			
			if (playing) //display icon while playing
			{
				cubeObject.DrawMesh(lampShader);
			}

			useTexture(elecHUD, NULL, NULL); //elec spell icon
			if (dynamic_cast<SpellDecorator*>(player->spells[0])->moveSpell) {
				lampShader.setVec3("objectColor", glm::vec3(1.0, 0.2, 0.2));
			}
			else
				lampShader.setVec3("objectColor", glm::vec3(1.0, 1.0, 1.0));
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.90f, 0.865f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 0, 1));
			model = glm::scale(model, glm::vec3(0.095f, 0.127f, 1.0f));
			lampShader.setMat4("projection", glm::mat4(1.0));
			lampShader.setMat4("model", model);
			lampShader.setMat4("view", glm::mat4(1.0));
			
			if (playing) //display icon while playing
			{
				cubeObject.DrawMesh(lampShader);
			}
			unbindTextures();

			useTexture(iceHUD, NULL, NULL); //ice spell icon

			if (dynamic_cast<SpellDecorator*>(player->spells[1])->moveSpell) {
				lampShader.setVec3("objectColor", glm::vec3(1.0, 0.2, 0.2));
			}
			else
				lampShader.setVec3("objectColor", glm::vec3(1.0, 1.0, 1.0));

			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.71f, 0.865f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 0, 1));
			model = glm::scale(model, glm::vec3(0.095f, 0.127f, 1.0f));
			lampShader.setMat4("projection", glm::mat4(1.0));
			lampShader.setMat4("model", model);
			lampShader.setMat4("view", glm::mat4(1.0));
			
			if (playing) //display icon while playing
			{
				cubeObject.DrawMesh(lampShader);
			}
			unbindTextures();

			useTexture(fireHUD, NULL, NULL); // fire spell icon

			if (dynamic_cast<SpellDecorator*>(player->spells[2])->moveSpell) {
				lampShader.setVec3("objectColor", glm::vec3(1.0, 0.2, 0.2));
			}
			else
				lampShader.setVec3("objectColor", glm::vec3(1.0, 1.0, 1.0));

			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-0.5275f, 0.8655f, 0.0f));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 0, 1));
			model = glm::scale(model, glm::vec3(0.095f, 0.127f, 1.0f));
			lampShader.setMat4("projection", glm::mat4(1.0));
			lampShader.setMat4("model", model);
			lampShader.setMat4("view", glm::mat4(1.0));
			
			if (playing) //display icon while playing
			{
				cubeObject.DrawMesh(lampShader);
			}

			glEnable(GL_DEPTH_TEST);
			unbindTextures(); //remember to unbind textures after you apply them, and before using a new texture.
		}


		if (pass == 1) { // second pass

			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glDepthMask(GL_FALSE);
			glDisable(GL_DEPTH_TEST);

			outlineShader.use();
			outlineShader.setMat4("view", view);
			outlineShader.setMat4("projection", projection);

			useTexture(playerDiffuse, NULL, NULL);
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(player->g_object.position.x, player->g_object.position.y - 0.02f, player->g_object.position.z));
			model = glm::rotate(model, glm::radians(-player->g_object.angle), glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(0.52f));
			outlineShader.setMat4("model", model);
			bossObject.DrawMesh(outlineShader);

			glStencilMask(0xFF);


			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);
		}
	}
}


void Scene::collisions()
{
	cd.planeCollision(player->g_object.colObj, ground->g_object.colObj);
	player->grounded = c_data.CollisionAgainstPlane(player->g_object.colObj, ground->g_object.colObj);

	//player wall/box collisions
	for (int i = 0; i < 8; i++) {

		if (i < 4) cd.playerBoxCollision(player->g_object, wall[i]->g_object.colObj);

		cd.playerBoxCollision(player->g_object, crates[i]->g_object.colObj);
		player->g_object.position = player->g_object.colObj->getPosition();
		cd.npcBoxCollision(dynamic_cast<NPC*>(boss)->g_object, crates[i]->g_object.colObj);
		boss->setPosition(dynamic_cast<NPC*>(boss)->g_object.colObj->getPosition());

		for (int j = 0; j < 3; j++) {
			cd.SpellBoxCollision(player->spells[j], boss, dynamic_cast<SpellDecorator*>(player->spells[j])->object.colObj, dynamic_cast<NPC*>(boss)->g_object.colObj);
			dynamic_cast<SpellDecorator*>(player->spells[j])->object.position = dynamic_cast<SpellDecorator*>(player->spells[j])->object.colObj->getPosition();

			cd.SpellBoxCollision(dynamic_cast<SpellDecorator*>(player->spells[j])->object.colObj, crates[i]->g_object.colObj);
			dynamic_cast<SpellDecorator*>(player->spells[j])->object.position = dynamic_cast<SpellDecorator*>(player->spells[j])->object.colObj->getPosition();

			cd.SpellBoxCollision(dynamic_cast<NPC*>(boss)->getSpell(j)->getColObj(), crates[i]->g_object.colObj);
			dynamic_cast<NPC*>(boss)->getSpell(j)->setPosition(dynamic_cast<NPC*>(boss)->getSpell(j)->getColObj()->getPosition());
		}
	}
}


bool Scene::updateScene()
{
	if (playing)
	{
		collisions(); // call before objects update
		dynamic_cast<NPC*>(boss)->update(player);
		keyboard.handlePlayerkeyboard(player);
		mouse.MouseMotion(player);
		player->update();
		
		collisions(); // call after objects update

		// lose condition, will close the application if this happens
		if (player->getHealth() <= 0.0f)
		{
			isLost = true;
			playing = false;
		}
		else if (dynamic_cast<NPC*>(boss)->getHealth() <= 0.0f)
		{
			isWon = true;
			playing = false;
		}
	}

	if (isWon && !playing)
	{
		winTimer -= 1;

		if (winTimer == 0)
		{
			isWon = false;
			winTimer = 500;
			playing = true;
		}
	}

	if (isLost && !playing)
	{
		loseTimer -= 1;

		if (loseTimer == 0)
		{
			return false;
		}
	}

	return true;
}