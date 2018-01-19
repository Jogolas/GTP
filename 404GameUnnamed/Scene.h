#pragma once
#include "Camera.h"
#include "Shader.h"
#include <stack>
#include "Environment.h"
#include "Collider.h"
#include "CollisionData.h"

class Scene
{
public:
	Scene();

	void updateScene();
	void drawScene();
	void collisions();

private:
	GLuint loadCubeMap(const char *fname[6], GLuint *texID);
	GLuint meshID[4], skyProgram;
	GLuint program[2];
	GLuint skybox[5];
	Player *player;
	Environment *ground;
	Environment *wall[4];
	AbstractAI *boss;
	Camera* cam;
	Mesh meshes[4];
	Shader* shader;
	CollisionData* cd;
	std::stack<glm::mat4> mvStack;
	//Collision collision;
};

