#ifndef SCENE_H
#define SCENE_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Shader.h"
#include "Model.h"

#include "Environment.h"
#include "Player.h"

#include "InputManager.h"

#include "AStar_pathing.h"

class Scene
{
public:
	Scene() {}
	Scene(bool active);
	void updateScene();
	void drawScene();

private:
	GLuint loadCubeMap(const char *fname[6], GLuint *texID);

	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	Model cubeObject, bossObject, wallmodel;
	Shader lightingShader, lampShader;

	Player* player;
	Environment* ground;
	Environment* wall[4];
	Environment* crates[8];
	MouseHandler mouse;
};

#endif