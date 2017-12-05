#include "AttackState.h"
#include "NPC.h"
#include "AIController.h"
#include "Player.h"

AttackState::AttackState()
{
	////not the ideal place to create this, testing for now
	fireBlast = new AISpellDecorator(new Element(new Burning(npc), "Fire Blast", 100.0f));
}

bool move = false;
GLfloat timer = 100.0f;

void AttackState::handle(AIController* a)
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	npc = a->getNPC();
	a->findTarget(a->getTarget(), 3, move);
	timer--;

	if (!move) {
		dynamic_cast<NPC*>(npc)->setSpell(fireBlast);
		dynamic_cast<NPC*>(npc)->getSpell()->fireForward(npc, a->getTarget()->getPosition());
	}

	glm::vec3 distance = a->getTarget()->getPosition() - dynamic_cast<NPC*>(npc)->getPosition();
	
	if (length(distance) < 3) {
		Entity* player = a->getTarget();
		player->setPosition(glm::vec3(player->getPosition().x + dynamic_cast<NPC*>(npc)->getPosition().x))
	}

	if (timer < 0) {
		if (move) {
			move = false;
			fireBlast->setPosition(dynamic_cast<NPC*>(npc)->getPosition());
		}
		else move = true;

		timer = 200.0f;
	}


	if (keys[SDL_SCANCODE_2]) {
		a->switchCurrentState(a->getIdleState());
	}
}