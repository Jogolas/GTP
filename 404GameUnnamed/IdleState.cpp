#include "IdleState.h"

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
	//code to handle boss idle state
}