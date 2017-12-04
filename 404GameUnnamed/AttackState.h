#pragma once
#include "AbstractAIState.h"

class AttackState : public AbstractAIState
{
public:
	AttackState();
	virtual ~AttackState() {}
	void handle(AIController* a);

private:
	AbstractAI* npc;
};