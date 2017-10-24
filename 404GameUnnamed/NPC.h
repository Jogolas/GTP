#pragma once
#include "AbstractAIState.h"
#include "IdleState.h"
#include "AttackState.h"
#include "glm.hpp"


class NPC : AbstractAI
{
public: //methods
	NPC(glm::vec3 position);
	~NPC() { delete this; }
	void render();
	void collider();
	AbstractAIState* getState();
	void switchCurrentState(AbstractAIState* state);

private:
	AbstractAIState* idle;
	AbstractAIState* attack;
	AbstractAIState* current;
};