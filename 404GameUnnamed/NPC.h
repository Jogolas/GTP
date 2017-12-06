#pragma once
#include "AIController.h"
#include "Renderer.h"
#include "Graph.h"
#include "AISpellDecorator.h"
#include "DrawableObject.h"


class NPC : public AbstractAI, public DrawableObject
{
public: //methods
	NPC();
	NPC(glm::vec3 position);
	~NPC() { delete this; }

	void update();
	void findPath(CGraph* node);
	void returnToCenter();
	void moveNPC();

	GLfloat getHealth() { return health; }

	AIController* getController() { return controller; }

	AISpellDecorator* getSpell() { return spell; }
	AISpellDecorator* setSpell(AISpellDecorator* s) { return spell = s; }

	glm::mat4 draw(glm::mat4 modelMatrix);

	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 pos) { return position = pos; }

	Entity* getGameObject() { return npc; }
	Entity* setGameObject(Entity* object) { return npc = object; }

	Mesh getMesh() { return mesh; }
	Mesh setMesh(Mesh mesh) { return this->mesh = mesh; }

private:
	//methods
	void closestNode(glm::vec3 tar, CGraph* nodes);

	Entity* npc;
	Mesh mesh;

	AIController* controller;
	AISpellDecorator* spell;

	//variables
	GLfloat health;
	glm::vec3 position;
	glm::vec3 veloctiy;
};