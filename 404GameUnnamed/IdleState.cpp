#include "IdleState.h"
#include "NPC.h"
#include <SDL.h>
#include "AIController.h"


void IdleState::handle(AIController* a)
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	a->getNPC()->returnToCenter();
	if (keys[SDL_SCANCODE_1]) {
		a->switchCurrentState(a->getAttackState());
	}
}