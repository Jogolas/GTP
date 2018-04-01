#pragma once
#include "AbstractAIState.h"

class AttackState : public AbstractAIState
{
public:
	AttackState() {}
	virtual ~AttackState() {}
	void handle(AbstractAI* npc);

public:
	bool chasing = false;
	bool fireProjectile = true;
	bool spellFired = false;
	float timer = 500;
};