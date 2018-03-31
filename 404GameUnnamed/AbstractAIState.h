#pragma once
#include "AbstractAI.h"

class AbstractAIState
{
public:
	virtual ~AbstractAIState() {}
	virtual void handle(AbstractAI* npc) = 0;

};