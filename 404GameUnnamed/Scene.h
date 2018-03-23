#ifndef SCENE_H
#define SCENE_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Shader.h"
#include "Camera.h"
#include "FBXLoader.h"

#include "Environment.h"
#include "Player.h"

#include "AStar_pathing.h"

class Scene
{
public:
	Scene() {}
	Scene(bool active);
	void updateScene();
	void drawScene();
	void mouseMotion(GLuint x, GLuint y);

private:
	GLuint loadCubeMap(const char *fname[6], GLuint *texID);

	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	FBXLoader cubeObject, bossObject;
	Shader lightingShader, lampShader;

	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
};

#endif