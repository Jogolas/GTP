#include "IdleState.h"
#include "NPC.h"
#include <SDL.h>
#include "AIController.h"


void IdleState::handle(AIController* a)
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	glm::vec3 position = glm::vec3(0, 0, 0);
	a->getNPC()->findRotation(position);

	if (keys[SDL_SCANCODE_1]) {
		a->switchCurrentState(a->getAttackState());
	}
}