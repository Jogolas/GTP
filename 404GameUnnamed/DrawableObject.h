#pragma once
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"

class DrawableObject
{
public:
	DrawableObject() {}
	virtual ~DrawableObject() {}

	virtual glm::mat4 Translation() = 0;
	virtual glm::mat4 Rotation() = 0;
	virtual glm::mat4 Scaled() = 0;

	virtual glm::mat4 resetMatrix() = 0;
	virtual glm::mat4 getMatrix() = 0;

	virtual void updateTransforms(glm::vec3 pos, float angle, glm::vec3 rot, glm::vec3 scale) = 0;

	virtual Shader getShader() = 0;
	virtual Model getModel() = 0;
};