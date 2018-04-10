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
	bool updateScene();
	void drawScene();

	void collisions();
	void setupMaterial(Shader shader, float shininess);
	void setupPointLight(Shader shader, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void setupDirLight(Shader shader, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void useTexture(GLuint diffuse, GLuint specular, GLuint emission);
	void unbindTextures();

private:
	GLuint loadCubeMap(const char *fname[6], GLuint *texID);
	GLuint diffuseMap, specularMap, emissionMap;
	GLuint groundDiffuse, groundSpecular, groundEmission;
	GLuint PlayerHUD, PlayerWin, PlayerLose, playerDiffuse, playerSpecular, playerEmission;
	GLuint fireHUD, iceHUD, elecHUD;
	GLuint bossDiffuse, bossSpecular, bossEmission;
	GLuint windowTexture;

	glm::vec3 pointLightPositions[4] = 
	{
		glm::vec3(25.0f, 5.0f, 25.0f),
		glm::vec3(25.0f, 5.0f, -25.0f),
		glm::vec3(-25.0f, 5.0f, 25.0f),
		glm::vec3(-25.0f, 5.0f, -25.0f)
	};

	glm::vec3 dirLightPosition = glm::vec3(-20.0f, -10.0f, -20.0f);

	Model cubeObject, bossObject, LampObject;
	Shader lightingShader, lampShader, celShader, outlineShader;

	Player* player;

	AbstractAI* boss;

	Environment* ground;
	Environment* wall[4];
	Environment* crates[8];

	MouseHandler mouse;
	KeyboardHandler keyboard;
	CollisionHandler cd;

	//win/lose conditions
	bool isWon = false, isLost = false, playing = true;
	int winTimer = 500, loseTimer = 500;

};

#endif