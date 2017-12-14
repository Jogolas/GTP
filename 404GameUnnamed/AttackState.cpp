#include "AttackState.h"
#include "NPC.h"
#include "AIController.h"
#include "Player.h"

AttackState::AttackState()
{
}

bool move = false;
GLfloat timer = 100.0f;
glm::vec3 tmpPosition;

void AttackState::handle(AIController* a)
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	npc = a->getNPC();
	
	a->findTarget(a->getTarget(), 3);
	timer--;

	if (!move && dynamic_cast<NPC*>(npc)->getSpell() != nullptr) {
		dynamic_cast<NPC*>(npc)->getSpell()->fireForward(npc, tmpPosition);
	}
	else if(move) dynamic_cast<NPC*>(npc)->moveNPC();
	

	if (timer < 0) {
		if (move) {
			dynamic_cast<NPC*>(npc)->getSpell()->setPosition(npc->getPosition());
			tmpPosition = a->getTarget()->getPosition();
			move = false;
		}
		else {
			tmpPosition = glm::vec3(0, 0, 0);
			move = true;
		}

		timer = 200.0f;
	}


	if (keys[SDL_SCANCODE_2]) {
		a->switchCurrentState(a->getIdleState());
	}
}