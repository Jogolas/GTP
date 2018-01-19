#pragma once
#include "AbstractAIState.h"
#include "AISpellDecorator.h"

class AttackState : public AbstractAIState
{
public:
	AttackState();
	virtual ~AttackState() {}
	void handle(AIController* a);

private:
	AbstractAI* npc;
};