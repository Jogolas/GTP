#include "AttackState.h"
#include "NPC.h"
#include "AIController.h"

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

	a->findTarget(a->getTarget(), 5, move);
	timer--;

	if (!move) {
		npc = a->getNPC();
		dynamic_cast<NPC*>(npc)->setSpell(fireBlast);
		dynamic_cast<NPC*>(npc)->getSpell()->fireForward(npc, a->getTarget()->getPosition());
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