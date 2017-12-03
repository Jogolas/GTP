#include "IdleState.h"
#include "NPC.h"
#include <SDL.h>

AbstractAIState* IdleState::CurrentState(AbstractAI* a)
{
	return nullptr;
}

AbstractAIState* IdleState::SwitchState(AbstractAI* a)
{
	//code to switch to attack state when player starts combat
	return nullptr;
}

void IdleState::handle(AbstractAI* a)
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	glm::vec3 position = glm::vec3(0, 0, 0);
	dynamic_cast<NPC*>(a)->findRotation(position);

	if (keys[SDL_SCANCODE_1]) {
		dynamic_cast<NPC*>(a)->switchCurrentState(dynamic_cast<NPC*>(a)->getAttackState());
	}
}