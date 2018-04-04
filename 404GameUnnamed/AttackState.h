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
	bool chasing;
	bool fireProjectile;
	bool spellFired;
	float timer = 500;
};