#pragma once
#include "glm.hpp"

class AbstractSpell
{
public:
	virtual void handleSpell() = 0;
	virtual float spellDamage(float dmg) = 0;

	virtual glm::mat4 draw() = 0;
};