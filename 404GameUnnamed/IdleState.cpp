#include "IdleState.h"
#include "NPC.h"
#include "Player.h"


void IdleState::handle(AbstractAI* npc)
{
	if (timer >= 0) timer--;
	else {
		dynamic_cast<NPC*>(npc)->controller.attacked = true;
		std::cout << "Boss was attacked" << std::endl;
	}

	dynamic_cast<NPC*>(npc)->controller.switchState();
}