#pragma once

#include "AbstractAIState.h"

class AttackState : public AbstractAIState
{
public:
	AttackState();
	virtual ~AttackState() {}
	AbstractAIState* CurrentState(AbstractAI* a);
	AbstractAIState* SwitchState(AbstractAI* a);
	void handle(AbstractAI* a);

private:
	AbstractAI* npc;
};