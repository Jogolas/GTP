#pragma once
#include "DrawableObject.h"

class D_Object : public DrawableObject
{
public:
	D_Object();
	D_Object(Model model, Shader shader);
	~D_Object();

	glm::mat4 Translation();
	glm::mat4 Rotation();
	glm::mat4 Scaled();

	glm::mat4 resetMatrix();
	glm::mat4 getMatrix() { return matrix; }

	void updateTransforms(glm::vec3 pos, float angle, glm::vec3 rot, glm::vec3 scale);

	Shader getShader() { return shader; }
	Model getModel() { return model; }

private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 vRot;
	GLfloat fRotation;

	glm::mat4 matrix;

	Shader shader;
	Model model;
};