#include "AttackState.h"
#include "NPC.h"
#include "AIController.h"

AttackState::AttackState()
{

}


void AttackState::handle(AIController* a)
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);



	a->getNPC()->findRotation(a->getTarget()->getPosition());
	if (keys[SDL_SCANCODE_2]) {
		a->switchCurrentState(a->getIdleState());
	}
}