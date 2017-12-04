#pragma once
#include "AIController.h"

class AttackState : public AbstractAIState
{
public:
	AttackState();
	virtual ~AttackState() {}
	AbstractAIState* CurrentState(AbstractAI* a);
	AbstractAIState* SwitchState(AbstractAI* a);
	void handle(AIController* a);

private:
	AbstractAI* npc;
};