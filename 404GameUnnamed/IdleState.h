#pragma once
#include "AbstractAIState.h"

class IdleState : public AbstractAIState
{
public:
	IdleState() {}
	virtual ~IdleState() { }
	void handle(AbstractAI* npc);

	float lastHealth;
	bool firstRun = true;
};