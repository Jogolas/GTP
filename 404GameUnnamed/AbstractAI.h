#pragma once
#include "glm.hpp"

class AbstractAI
{
public:
	virtual ~AbstractAI() {}
	virtual glm::vec3 getPosition() = 0;
	virtual glm::vec3 setPosition(glm::vec3 pos) = 0;

	virtual float getRotation() = 0;
	virtual float setRotation(float rot) = 0;

	virtual float removeHealth(float amount) = 0;
};