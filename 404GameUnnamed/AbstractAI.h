#pragma once

#include "Renderer.h"
#include "Collider.h"

class AbstractAI
{
public:
	virtual ~AbstractAI() {}
	virtual void render() = 0;
	virtual void collider() = 0;
	virtual void switchCurrentState(AbstractAIState* state) = 0;
	virtual AbstractAIState* getState() = 0;
};