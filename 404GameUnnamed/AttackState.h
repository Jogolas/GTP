#pragma once

#include "AbstractAIState.h"

class AttackState : public AbstractAIState
{
public:
	AttackState() {}
	~AttackState() { delete this; }
	AbstractAIState* CurrentState(AbstractAI* a);
	AbstractAIState* SwitchState(AbstractAI* a);
	void handle(AbstractAI* a);
};