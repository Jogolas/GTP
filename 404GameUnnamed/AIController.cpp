#include "AIController.h"
#include "IdleState.h"
#include "AttackState.h"
#include "NPC.h"


AIController::AIController()
{
	idle = new IdleState();
	attack = new AttackState();

	current = idle;
}

AIController::AIController(AbstractAI* npc)
{
	_npc = npc;

	idle = new IdleState();
	attack = new AttackState();

	current = idle;
}


AIController::~AIController()
{
	delete this;
}

void AIController::handleState()
{
	if (current == idle) {
		dynamic_cast<IdleState*>(current)->handle(this);
	}
	if (current == attack) {
		dynamic_cast<AttackState*>(current)->handle(this);
	}
}

void AIController::switchCurrentState(AbstractAIState* state)
{
	current = state;
}


glm::vec3 AIController::moveForward(glm::vec3 pos, GLfloat angle, GLfloat d)
{
	return glm::vec3(pos.x + (d * std::sin(angle)), pos.y, pos.z - (d*std::cos(angle)));
}