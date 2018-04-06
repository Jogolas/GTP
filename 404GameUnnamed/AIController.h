#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "AbstractAI.h"
#include "AbstractAIState.h"
#include "Player.h"

class AIController
{
public:
	AIController() {}
	AIController(AbstractAI* npc);

	void moveNPC();
	void setTarget(Player* target);
	Player* getTarget() { return target; }
	void switchState();
	void handleState();


	//variables
public:
	bool moving = false;
	bool attacked = false;

private:
	AbstractAI* npc;
	AbstractAIState *current, *idle, *attack;

	Player* target;

	float meleeInterval;
};

#endif // !AICONTROLLER_H