#pragma once
#include "glm.hpp"

class AbstractAI
{
public:
	virtual ~AbstractAI() {}
	virtual void returnToCenter() = 0;
	virtual glm::vec3 getPosition() = 0;
};