#pragma once
#include "Camera.h"
#include "Shader.h"
#include <stack>
#include "Environment.h"
#include "Collider.h"

class Scene
{
public:
	Scene();

	void updateScene();
	void drawScene();

private:
	GLuint loadCubeMap(const char *fname[6], GLuint *texID);
	GLuint meshID[4], skyProgram;
	GLuint program[2];
	GLuint skybox[5];
	DrawableObject *player, *ground, *boss;
	DrawableObject *wall[4];
	Camera* cam;
	Mesh meshes[4];
	Shader* shader;
	std::stack<glm::mat4> mvStack;
	//Collision collision;
};

