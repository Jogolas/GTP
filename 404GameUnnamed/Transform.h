#pragma once
#include "Forces.h"
#include "glm\glm.hpp"
#include"glm\gtc\matrix_access.hpp"

class Transform
{
public:
	Transform();
	virtual ~Transform() {}

	void Translate(const vec3& translation);
	void Scale(const vec3& scaling);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	vec3 getPosition() const;
	vec3 getScale() const;
	vec3 getOrientation() const;
	vec3 getVerticalDirection() const;
	vec3 getHorizontalDirection() const;
	vec3 getFrontDircetion() const;

	mat4 localToWorldMatrix();
	mat4 worldToLocalMatrix();

private:
	mat4 transformMatrix;
};