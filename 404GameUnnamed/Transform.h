#pragma once
#include "glm.hpp"
#include "gtc\matrix_access.hpp"

class Transform
{
public:
	Transform();
	virtual ~Transform() {}

	void Translate(const glm::vec3& translation);
	void Scale(const glm::vec3& scaling);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	glm::vec3 getPosition() const;
	glm::vec3 getScale() const;
	glm::vec3 getOrientation() const;
	glm::vec3 getVerticalDirection() const;
	glm::vec3 getHorizontalDirection() const;
	glm::vec3 getFrontDircetion() const;

	glm::mat4 localToWorldMatrix();
	glm::mat4 worldToLocalMatrix();

private:
	glm::mat4 transformMatrix;
};