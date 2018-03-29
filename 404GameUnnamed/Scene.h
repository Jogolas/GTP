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

	void collisions();
	void setupMaterial(Shader shader, float shininess);
	void setupLight(Shader shader, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

private:
	GLuint loadCubeMap(const char *fname[6], GLuint *texID);
	GLuint diffuseMap, specularMap, emissionMap;

	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	glm::vec3 orange = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::vec3 green = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 white = glm::vec3(1.0f);
	glm::vec3 grey = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 pink = glm::vec3(1.0f, 0.5f, 1.0f);
	glm::vec3 cyan = glm::vec3(0.5f, 1.0f, 1.0f);

	Model cubeObject, bossObject, wallmodel;
	Shader lightingShader, lampShader;

	Player* player;

	Environment* ground;
	Environment* wall[4];
	Environment* crates[8];

	MouseHandler mouse;
	CollisionHandler cd;
};

#endif