#pragma once
#include "AbstractAIState.h"
#include "SpellList.h"

class AttackState : public AbstractAIState
{
public:
	AttackState(AbstractAI* npc);
	virtual ~AttackState() {}
	void handle(AbstractAI* npc);

public:
	AISpellList spells;
	bool chasing = false;
	bool fireProjectile = true;
	bool spellFired = false;
	float timer = 500;
};