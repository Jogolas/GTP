#pragma once
#include "Renderer.h"
#include "Graph.h"
#include "AISpellDecorator.h"
#include "DrawableObject.h"
#include "CollisionHandler.h"
#include "AIController.h"
#include "AbstractAI.h"
#include "AISpellDecorator.h"


class NPC : public AbstractAI
{
public: //methods
	NPC();
	NPC(glm::vec3 position, glm::vec3 scale, float health);
	~NPC() 
	{ 
		delete this; 
	}

	void update(Player* p);
	glm::mat4 draw();

	GLfloat getHealth() { return health; }

	glm::vec3 getPosition() { return g_object.position; }
	glm::vec3 setPosition(glm::vec3 pos) { return g_object.position = pos; }

	float getRotation() { return g_object.angle; }
	float setRotation(float rot) { return g_object.angle = rot; }

	float removeHealth(float amount) { health -= amount; }

	AbstractAISpell* getSpell() { return spell; }

	AbstractAISpell* setSpell(AbstractAISpell* spell) { return this->spell = spell; }

	DrawableObject* getDrawingObject() { return d_object; }

public:
	AIController controller;
	AbstractAISpell* spell;

	Entity g_object;
	Transform tMat;

private:
	float health = 10000.0f;

	DrawableObject* d_object;

	glm::vec3 scale;
};