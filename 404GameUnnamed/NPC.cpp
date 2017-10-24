#include "NPC.h"

NPC::NPC(glm::vec3 position)
{
	idle = new IdleState();
	attack = new AttackState();
}

void NPC::render() 
{
	//code to render in model
}

void NPC::collider() 
{
	//code to set up collider
}

AbstractAIState* NPC::getState()
{
	return current;
}

void NPC::switchCurrentState(AbstractAIState* state)
{
	current = state;
}