#pragma once
#include "AISpellDecorator.h"
#include "SpellDecorator.h"
#include "NPC.h"

struct AISpellList
{
	void setupSpell()
	{
		spells[0] = new AISpellDecorator(new SpellType("Fast Spell", 20.0f, 1.2f), glm::vec3(0.2f));
		spells[1] = new AISpellDecorator(new SpellType("Slow Spell", 60.0f, 0.6f), glm::vec3(1.2f));
		spells[2] = new AISpellDecorator(new SpellType("normal Spell", 40.0f, 0.8f), glm::vec3(0.6f));
	}

	AbstractAISpell* spells[3];
};