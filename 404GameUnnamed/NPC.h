#pragma once
#include "Renderer.h"
#include "Graph.h"
#include "AISpellDecorator.h"
#include "DrawableObject.h"
#include "CollisionHandler.h"
#include "AIController.h"
#include "AbstractAI.h"


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

	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 pos) { return position = pos; }

	float getRotation() { return rotation; }
	float setRotation(float rot) { return rotation = rot; }

	Collider* getColObject() { return colObj; }

	DrawableObject* getDrawingObject() { return d_object; }

public:
	AIController controller;

private:
	float rotation = 0.0f;
	float health;

	Collider* colObj;
	Mesh mesh;

	DrawableObject* d_object;

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 veloctiy;
};