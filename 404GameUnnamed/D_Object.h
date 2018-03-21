#pragma once

#include "DrawableObject.h"

class D_Object : public DrawableObject
{
public:
	D_Object();
	~D_Object();

	glm::mat4 draw(glm::mat4 modelMatrix);
	
	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 pos) { return position = pos; }

	glm::vec3 getScale() { return scale; }
	glm::vec3 setScale(glm::vec3 scale) { return this->scale = scale; }

	glm::vec3 getVectorRotation() { return vRot; }
	glm::vec3 setVectorRotation(glm::vec3 rot) { return vRot = rot; }

	GLfloat getFloatRotation() { return fRotation; }
	GLfloat setFloatRotation(GLfloat rot) { return fRotation = rot; }

	Mesh getMesh() { return mesh; }
	Mesh setMesh(Mesh mesh) { return this->mesh = mesh; }

	FBXLoader getFBXMesh() { return fbxMesh; }
	FBXLoader setFBXMesh(FBXLoader fbxMesh) { return this->fbxMesh = fbxMesh; }

private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 vRot;
	GLfloat fRotation;

	Mesh mesh;
	FBXLoader fbxMesh;
};