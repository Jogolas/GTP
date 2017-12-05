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
	GLuint cubeMeshID, bunnyMeshID, skyProgram;
	GLuint program[1];
	GLuint currProgram;
	GLuint skybox[5];
	GameObject* player;
	GameObject* ground;
	GameObject* wall[4], *box[4];
	Camera* cam;
	Mesh meshes[2];
	Shader* shader;
	std::stack<glm::mat4> mvStack;
	//Collision collision;
};

