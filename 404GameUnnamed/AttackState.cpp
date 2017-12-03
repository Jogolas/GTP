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

void AttackState::handle(AbstractAI* a)
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);



	dynamic_cast<NPC*>(a)->findRotation(dynamic_cast<NPC*>(a)->getTarget()->getPosition());
	if (keys[SDL_SCANCODE_2]) {
		dynamic_cast<NPC*>(a)->switchCurrentState(dynamic_cast<NPC*>(a)->getIdleState());
	}
}