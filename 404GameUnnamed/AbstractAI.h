#pragma once
#include "Collider.h"

class AbstractAI
{
public:
	virtual ~AbstractAI() {}
	virtual glm::mat4 draw() = 0;
	virtual void returnToCenter() = 0;
};