#pragma once

#include "AbstractAIState.h"

class IdleState : public AbstractAIState
{
public:
	IdleState() {}
	~IdleState() { delete this; }
	AbstractAIState* CurrentState(AbstractAI* a);
	AbstractAIState* SwitchState(AbstractAI* a);
	void handle(AbstractAI* a);
};