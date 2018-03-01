#pragma once
#include "Camera.h"
#include "Shader.h"
#include <stack>
#include <list>
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
	Environment *wall[3];
	Environment *UI[1];
	AbstractAI *boss;
	//std::list<AbstractAI> *enemies = new std::list<AbstractAI>();
	Camera* cam;
	Mesh meshes[4];
	Shader* shader;
	CollisionData* cd;
	std::stack<glm::mat4> mvStack;
	//Collision collision;
};

