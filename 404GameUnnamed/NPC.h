#pragma once
#include "AIController.h"
#include "Renderer.h"
#include "Graph.h"
#include "AISpellDecorator.h"
#include "DrawableObject.h"


class NPC : public AbstractAI
{
public: //methods
	NPC();
	NPC(glm::vec3 position);
	~NPC() { delete this; }

	void update();
	void findPath(CGraph* node);
	void returnToCenter();
	void moveNPC();
	glm::mat4 draw(glm::mat4 modelMatrix, glm::vec3 scale);

	GLfloat getHealth() { return health; }

	AIController* getController() { return controller; }

	AISpellDecorator* getSpell() { return spell; }

	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 pos) { return position = pos; }

	Entity* getGameObject() { return npc; }

	DrawableObject* getDrawingObject() { return d_object; }


private:
	//methods
	void closestNode(glm::vec3 tar, CGraph* nodes);

	Entity* npc;
	Mesh mesh;

	AIController* controller;
	AISpellDecorator* spell;

	DrawableObject* d_object;

	//variables
	GLfloat health;
	glm::vec3 position;
	glm::vec3 veloctiy;
};