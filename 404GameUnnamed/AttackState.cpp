#include "AttackState.h"

AbstractAIState* AttackState::CurrentState(AbstractAI* a)
{
	return a->getState();
}

AbstractAIState* AttackState::SwitchState(AbstractAI* a)
{
	//code to switch back to idle when combat ends with player.
}

void AttackState::handle(AbstractAI* a)
{
	//code to cycle through ablities during combat with player.
}