#include "IdleState.h"

AbstractAIState* IdleState::CurrentState(AbstractAI* a)
{
	return a->getState();
}

AbstractAIState* IdleState::SwitchState(AbstractAI* a)
{
	//code to switch to attack state when player starts combat
}

void IdleState::handle(AbstractAI* a)
{
	//code to handle boss idle state
}