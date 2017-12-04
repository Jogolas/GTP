#pragma once
#include "AIController.h"
#include "Renderer.h"
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
	void moveNPC();

	GLfloat getHealth() { return health; }
	Entity* getNPC() { return npc; }

	AIController* getController() { return controller; }

	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 pos) { return position = pos; }

private:
	//methods
	void closestNode(glm::vec3 tar, CGraph* nodes);
	void returnToCenter();

	Entity* npc;

	AIController* controller;

	//variables
	GLfloat health;
	GLfloat rotation;
	glm::vec3 position;

};