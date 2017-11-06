#include "AttackState.h"

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
	//code to cycle through ablities during combat with player.
}