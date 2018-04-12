#include "IdleState.h"
#include "NPC.h"
#include "Player.h"



void IdleState::handle(AbstractAI* npc)
{
	if (firstRun) {
		lastHealth = dynamic_cast<NPC*>(npc)->getHealth();
		firstRun = false;
	}

	if (dynamic_cast<NPC*>(npc)->getHealth() < lastHealth) {
		dynamic_cast<NPC*>(npc)->controller.attacked = true;
		std::cout << "Boss was attacked" << std::endl;
	}

	lastHealth = dynamic_cast<NPC*>(npc)->getHealth();

	dynamic_cast<NPC*>(npc)->controller.switchState();
}