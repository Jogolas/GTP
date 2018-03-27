#include "Scene.h"
#include "NPC.h"
#include "SDL_timer.h"

#include <iostream>

#define DEG_TO_RADIAN 0.017453293

Scene::Scene(bool active)
{
	player = new Player(glm::vec3(0.0f, -1.0f, 5.0f));
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

	lightingShader = Shader("simpleShader.vert", "simpleShader.frag");
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

	// view and projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(player->cam.Zoom), 800.0f / 600.0f, 1.0f, 500.0f);
	glm::mat4 view = player->cam.GetViewMatrix();

	lightingShader.setMat4("projection", projection);
	lightingShader.setMat4("view", view);

	// world transformations
	glm::mat4 model = player->draw();

	lightingShader.setMat4("model", model);
	bossObject.Draw(lightingShader);


	//ground
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	model = glm::mat4(1.0); // reset model matrix
	model = ground->draw();

	lightingShader.setMat4("model", model);
	cubeObject.DrawMesh(lightingShader);


	//walls
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	for (int i = 0; i < 4; i++) {
		model = glm::mat4(1.0); // reset model matrix
		model = wall[i]->draw();
		lightingShader.setMat4("model", model);
		cubeObject.DrawMesh(lightingShader);
	}

	for (int i = 0; i < 8; i++) {
		model = glm::mat4(1.0); // reset model matrix
		model = crates[i]->draw();
		lightingShader.setMat4("model", model);
		cubeObject.DrawMesh(lightingShader);
	}
}

//void drawScenes()
//{
//	glm::mat4 projection(1.0);
//	projection = glm::perspective(float(60.0f * DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 300.0f);
//
//
//	glm::mat4 modelview(1.0);
//
//	mvStack.push(modelview);
//	mvStack.top() = cam->draw(mvStack.top(), dynamic_cast<Player*>(player));
//
//	// skybox as single cube using cube map
//	glCullFace(GL_FRONT);
//	glUseProgram(skyProgram);
//	Renderer::setMatrix(skyProgram, "projection", glm::value_ptr(projection));
//	glDepthMask(GL_FALSE); // make sure writing to update depth test is off
//	glm::mat3 mvRotOnlyMat3 = glm::mat3(mvStack.top());
//	mvStack.push(glm::mat4(mvRotOnlyMat3));
//
//	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox[0]);
//	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(1.5f, 1.5f, 1.5f));
//	Renderer::setMatrix(skyProgram, "modelview", glm::value_ptr(mvStack.top()));
//	meshes[0].drawMesh(meshes[1].getMeshID());
//	mvStack.pop();
//	glCullFace(GL_BACK);
//
//
//	// back to remainder of rendering
//	glDepthMask(GL_TRUE); // make sure depth test is on
//
//	glm::vec4 tmp = mvStack.top() * lightPos;
//	light.position[0] = tmp.x;
//	light.position[1] = tmp.y;
//	light.position[2] = tmp.z;
//
//
//
//	shader->bindShaderProgram(program[0]);
//	shader->useMatrix4fv(projection, "projection");
//	Renderer::setLightPos(program[0], glm::value_ptr(tmp));
//
//	////ground
//	glBindTexture(GL_TEXTURE_2D, texture[1]);
//	glm::mat4 modelMatrix(1.0);
//	mvStack.push(mvStack.top());
//	modelMatrix = ground->draw(modelMatrix);
//	mvStack.top() *= modelMatrix;
//	shader->useMatrix4fv(mvStack.top(), "modelview");
//	ground->getDrawingObject()->getMesh().drawMesh(ground->getDrawingObject()->getMesh().getMeshID());
//	mvStack.pop();
//
//	//// walls
//	glBindTexture(GL_TEXTURE_2D, texture[2]);
//	for (GLuint i = 0; i < 4; i++) {
//
//		modelMatrix = glm::mat4(1.0); //reset modelmatrix
//		mvStack.push(mvStack.top());
//		modelMatrix = wall[i]->draw(modelMatrix);
//		mvStack.top() *= modelMatrix;
//		shader->useMatrix4fv(mvStack.top(), "modelview");
//		wall[i]->getDrawingObject()->getMesh().drawMesh(wall[i]->getDrawingObject()->getMesh().getMeshID());
//		mvStack.pop();
//	}
//
//	//// crates
//	glBindTexture(GL_TEXTURE_2D, texture[2]);
//	for (GLuint i = 0; i < 8; i++) {
//
//		modelMatrix = glm::mat4(1.0); //reset modelmatrix
//		mvStack.push(mvStack.top());
//		modelMatrix = crates[i]->draw(modelMatrix);
//		mvStack.top() *= modelMatrix;
//		shader->useMatrix4fv(mvStack.top(), "modelview");
//		crates[i]->getDrawingObject()->getMesh().drawMesh(crates[i]->getDrawingObject()->getMesh().getMeshID());
//		mvStack.pop();
//	}
//
//	shader->unbindShaderProgram();
//
//
//	shader->bindShaderProgram(program[1]);
//	shader->useMatrix4fv(projection, "projection");
//	Renderer::setLightPos(program[1], glm::value_ptr(tmp));
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox[0]);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, texture[0]);
//
//	////player
//	mvStack.push(mvStack.top());
//	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(0, 0, 0));
//	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(2, 2, 2));
//	shader->useMatrix4fv(mvStack.top(), "modelview");
//	fbxMesh.Draw(program[1]);
//	
//
//	//mvStack.push(mvStack.top());
//	//modelMatrix = glm::mat4(1.0); //reset model matrix
//	//modelMatrix = player->draw(modelMatrix, glm::vec3(1, 1, 1));
//	//fbxMesh.Draw(program[1]);
//	//mvStack.top() *= modelMatrix;
//	//shader->useMatrix4fv(mvStack.top(), "modelview");
//	//shader->useMatrix4fv(modelMatrix, "modelMatrix");
//	//GLuint uniformIndex = glGetUniformLocation(program[1], "cameraPos");
//	//glUniform3fv(uniformIndex, 1, glm::value_ptr(dynamic_cast<Player*>(player)->getEye()));
//	//Renderer::setMaterial(program[1], material);
//	////player->getDrawingObject()->getMesh().drawMesh(player->getDrawingObject()->getMesh().getMeshID());
//	//player->getDrawingObject()->getFBXMesh().Draw(program[1]);
//	//player->getDrawingObject()->getMesh().drawFBXMesh(program[1]);
//	//mvStack.pop();
//
//	////UI elements
//	glDisable(GL_DEPTH_TEST); // make sure writing to update depth test is off
//	glBindTexture(GL_TEXTURE_2D, UITexture[0]);
//	modelMatrix = glm::mat4(1.0); //reset modelmatrix
//	mvStack.push(mvStack.top());
//	modelMatrix = UI[0]->draw(modelMatrix);
//	mvStack.top() *= modelMatrix;
//	glm::value_ptr(glm::mat4(1.0));
//	shader->useMatrix4fv(mvStack.top(), "modelview");
//	GLuint uniformIndex = glGetUniformLocation(program[1], "cameraPos");
//	UI[0]->getDrawingObject()->getMesh().drawMesh(UI[0]->getDrawingObject()->getMesh().getMeshID());
//	mvStack.pop();
//	glEnable(GL_DEPTH_TEST);
//
//	glBindTexture(GL_TEXTURE_2D, texture[1]);
//	////boss
//	mvStack.push(mvStack.top());
//	modelMatrix = glm::mat4(1.0); //reset model matrix
//	modelMatrix = dynamic_cast<NPC*>(boss)->draw(modelMatrix);
//	mvStack.top() *= modelMatrix;
//	shader->useMatrix4fv(mvStack.top(), "modelview");
//	shader->useMatrix4fv(modelMatrix, "modelMatrix");
//	uniformIndex = glGetUniformLocation(program[1], "cameraPos");
//	glUniform3fv(uniformIndex, 1, glm::value_ptr(dynamic_cast<Player*>(player)->getEye()));
//	Renderer::setMaterial(program[1], material);
//	dynamic_cast<NPC*>(boss)->getDrawingObject()->getMesh().drawMesh(dynamic_cast<NPC*>(boss)->getDrawingObject()->getMesh().getMeshID());
//	mvStack.pop();
//	shader->unbindShaderProgram();
//
//	shader->bindShaderProgram(program[0]);
//	shader->useMatrix4fv(projection, "projection");
//
//	if (dynamic_cast<NPC*>(boss)->getSpell() != nullptr) {
//		glBindTexture(GL_TEXTURE_2D, texture[3]);
//		mvStack.push(mvStack.top());
//		mvStack.top() = glm::translate(mvStack.top(), dynamic_cast<NPC*>(boss)->getSpell()->getPosition());
//		mvStack.top() = glm::scale(mvStack.top(), glm::vec3(0.25f, 0.25f, 0.25f));
//		Renderer::setMatrix(program[0], "modelview", glm::value_ptr(mvStack.top()));
//		Renderer::drawObj(meshes[1].getMeshID(), meshes[1].getIndexCount(), GL_TRIANGLES);
//		mvStack.pop();
//	}
//
//
//	////node locations
//	for (int i = 0; i < 4; i++) {
//		mvStack.push(mvStack.top());
//		mvStack.top() = glm::translate(mvStack.top(), graph.GetNode(i)->debug_position);
//		mvStack.top() = glm::scale(mvStack.top(), glm::vec3(0.25f, 0.25f, 0.25f));
//		Renderer::setMatrix(program[0], "modelview", glm::value_ptr(mvStack.top()));
//		Renderer::drawObj(meshes[1].getMeshID(), meshes[1].getIndexCount(), GL_TRIANGLES);
//		mvStack.pop();
//	}
//
//
//	shader->unbindShaderProgram();
//
//	mvStack.pop(); //initial matrix
//}


void Scene::collisions()
{
	for (int i = 0; i < 8; i++) {
		cd.boxCollision(player->getColObject(), crates[i]->getColObject());
		player->setPosition(player->getColObject()->getPosition());
	}
}

void Scene::updateScene()
{
	player->update();
	collisions();
	mouse.MouseMotion(player);


}