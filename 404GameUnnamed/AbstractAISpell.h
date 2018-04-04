#pragma once
#include "Player.h"
#include "AbstractAI.h"

class AbstractAISpell
{
public:
	virtual ~AbstractAISpell() {};

	virtual void handleSpell(AbstractAI* npc, Player* target) = 0;
	virtual float spellDamage(float dmg) = 0;

	virtual glm::vec3 getPosition() = 0;
	virtual glm::vec3 setPosition(glm::vec3 pos) = 0;

	virtual Collider* getColObj() = 0;

	virtual glm::mat4 draw() = 0;

	virtual float getRotation() = 0;
	virtual float setRotation(float rot) = 0;
};