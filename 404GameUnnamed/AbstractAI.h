#pragma once
#include "glm.hpp"

class AbstractAI
{
public:
	virtual ~AbstractAI() {}
	virtual void returnToCenter() = 0;
};