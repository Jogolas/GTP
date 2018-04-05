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
	void useTexture(GLuint diffuse, GLuint specular, GLuint emission);

private:
	GLuint loadCubeMap(const char *fname[6], GLuint *texID);
	GLuint diffuseMap, specularMap, emissionMap;
	GLuint groundDiffuse, groundSpecular, groundEmission;
	GLuint PlayerHUD, playerDiffuse, playerSpecular, playerEmission;
	GLuint bossDiffuse, bossSpecular;

	glm::vec4 lightPos = glm::vec4(-0.2f, 3.0f, -0.3f, 1.0f);

	glm::vec3 orange = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::vec3 green = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 white = glm::vec3(1.0f);
	glm::vec3 grey = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 pink = glm::vec3(1.0f, 0.5f, 1.0f);
	glm::vec3 cyan = glm::vec3(0.5f, 1.0f, 1.0f);

	Model cubeObject, bossObject;
	Shader lightingShader, lampShader, celShader;

	Player* player;

	AbstractAI* boss;

	Environment* ground;
	Environment* wall[4];
	Environment* crates[8];

	MouseHandler mouse;
	CollisionHandler cd;

};

#endif