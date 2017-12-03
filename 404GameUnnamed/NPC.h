#pragma once
#include "AbstractAIState.h"
#include "IdleState.h"
#include "AttackState.h"
#include "Renderer.h"
#include "glm.hpp"
#include "Graph.h"
#include "GameObject.h"


class NPC : public AbstractAI
{
public: //methods
	NPC();
	NPC(glm::vec3 position);
	~NPC() { delete this; }

	glm::mat4 draw();
	void update();
	void findPath(CGraph* node);
	void findRotation(glm::vec3 tar);
	void switchCurrentState(AbstractAIState* state);
	void moveNPC();

	AbstractAIState* getState() { return current; }
	AbstractAIState* getAttackState() { return attack; }
	AbstractAIState* getIdleState() { return idle; }

	GLfloat getHealth() { return health; }
	GLfloat getRotation() { return rotation; }
	Entity* getNPC() { return npc; }

	Entity* getTarget() { return target; }
	Entity* setTarget(Entity* target) { return this->target = target; }

	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 pos) { return position = pos; }

private:
	//methods
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);
	void closestNode(glm::vec3 tar, CGraph* nodes);
	void returnToCenter();
	void handleState();

	Entity* npc;
	Entity* target;

	//variables
	GLfloat health;
	GLfloat rotation;
	glm::vec3 position;

	AbstractAIState* idle;
	AbstractAIState* attack;
	AbstractAIState* current;
};