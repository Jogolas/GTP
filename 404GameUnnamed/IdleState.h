#pragma once
#include "AbstractAIState.h"

class IdleState : public AbstractAIState
{
public:
	IdleState() {}
	virtual ~IdleState() { }
	void handle(AIController* a);
};