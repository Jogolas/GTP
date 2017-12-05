#include "AIController.h"
#include "IdleState.h"
#include "AttackState.h"
#include "NPC.h"

#define DEG_TO_RADIAN 0.017453293 //defined in .cpp to prevent redefinition.

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
		current->handle(this);
	}
	if (current == attack) {
		current->handle(this);
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

void AIController::findTarget(Entity* tar, GLuint l, bool move)
{
	glm::vec3 distance = tar->getPosition() - dynamic_cast<NPC*>(_npc)->getPosition();

	if (glm::length(distance) >= l) {
		rotation = (float)atan2(distance.z, distance.x) + (90 * DEG_TO_RADIAN);
		if (move) dynamic_cast<NPC*>(_npc)->moveNPC();
	}
}