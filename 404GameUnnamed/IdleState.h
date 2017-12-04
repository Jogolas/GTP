#pragma once
#include "AIController.h"

class IdleState : public AbstractAIState
{
public:
	IdleState() {}
	virtual ~IdleState() { }
	AbstractAIState* CurrentState(AbstractAI* a);
	AbstractAIState* SwitchState(AbstractAI* a);
	void handle(AIController* a);
};