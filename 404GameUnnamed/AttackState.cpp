#include "AttackState.h"
#include "NPC.h"


AttackState::AttackState()
{

}



AbstractAIState* AttackState::CurrentState(AbstractAI* a)
{
	return nullptr;
}

AbstractAIState* AttackState::SwitchState(AbstractAI* a)
{
	//code to switch back to idle when combat ends with player.
	return nullptr;
}

void AttackState::handle(AIController* a)
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);



	a->getNPC()->findRotation(a->getTarget()->getPosition());
	if (keys[SDL_SCANCODE_2]) {
		a->switchCurrentState(a->getIdleState());
	}
}