#pragma once
#include "glm.hpp"
#include "AbstractAIState.h"
#include "Entity.h"
#include <GL/glew.h>

class AIController
{
public:
	AIController();
	AIController(AbstractAI* npc);
	~AIController();

	void switchCurrentState(AbstractAIState* state);
	void handleState();

	GLfloat getRotation() { return rotation; }

	AbstractAIState* getState() { return current; }
	AbstractAIState* getAttackState() { return attack; }
	AbstractAIState* getIdleState() { return idle; }

	AbstractAI* getNPC() { return _npc; }

	Entity* getTarget() { return target; }
	Entity* setTarget(Entity* target) { return this->target = target; }

	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);

private:
	AbstractAIState* current;
	AbstractAIState* attack;
	AbstractAIState* idle;

	AbstractAI* _npc;
	
	GLfloat rotation;

	Entity* target;
};