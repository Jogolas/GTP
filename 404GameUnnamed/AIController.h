#pragma once
#include "glm.hpp"
#include "AbstractAIState.h"
#include <GL/glew.h>
#include "Player.h"

class AIController
{
public:
	AIController();
	AIController(AbstractAI* npc);
	~AIController();

	void findTarget(Player* tar, GLuint l);
	void switchCurrentState(AbstractAIState* state);
	void handleState();

	GLfloat getRotation() { return rotation; }

	AbstractAIState* getState() { return current; }
	AbstractAIState* getAttackState() { return attack; }
	AbstractAIState* getIdleState() { return idle; }

	AbstractAI* getNPC() { return _npc; }

	Player* getTarget() { return target; }
	Player* setTarget(Player* target) { return this->target = target; }

	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);

private:
	AbstractAIState* current;
	AbstractAIState* attack;
	AbstractAIState* idle;

	AbstractAI* _npc;
	
	GLfloat rotation;

	Player* target;
};