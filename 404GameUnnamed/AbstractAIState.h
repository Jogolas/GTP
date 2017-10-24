#pragma once

#include "AbstractAI.h"

class AbstractAIState
{
public:
	virtual ~AbstractAIState() {}
	virtual AbstractAIState* CurrentState(AbstractAI* a) = 0;
	virtual AbstractAIState* SwitchState(AbstractAI* a) = 0;
	virtual void handle(AbstractAI* a) = 0;
};