#pragma once
#include "AbstractAIState.h"

class IdleState : public AbstractAIState
{
public:
	IdleState() {}
	virtual ~IdleState() { }
	void handle(AbstractAI* npc);

	float timer = 500.0f;
};