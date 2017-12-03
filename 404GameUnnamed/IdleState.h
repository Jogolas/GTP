#pragma once

#include "AbstractAIState.h"

class IdleState : public AbstractAIState
{
public:
	IdleState() {}
	virtual ~IdleState() { }
	AbstractAIState* CurrentState(AbstractAI* a);
	AbstractAIState* SwitchState(AbstractAI* a);
	void handle(AbstractAI* a);
};