#pragma once
#include "AbstractAI.h"

class AIController; //pre-definition

class AbstractAIState
{
public:
	virtual ~AbstractAIState() {}
	virtual void handle(AIController* a) = 0;

};