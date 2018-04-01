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
	glm::vec3 moveNPCForward(glm::vec3 pos, float angle, float d); // should really make a class that does this stuff instead of typing it everywhere.

	AbstractAI* npc;
	AbstractAIState *current, *idle, *attack;

	Player* target;
};

#endif // !AICONTROLLER_H