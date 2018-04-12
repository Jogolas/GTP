#pragma once
#include "AbstractSpell.h"
#include "Player.h"

class SpellDecorator : public AbstractSpell
{
public:
	SpellDecorator();
	SpellDecorator(Player* p, const char* name, float dmg, float speed, float size, float timer, float cd);
	void handleSpell();
	float spellDamage(float dmg) { return damage += dmg; }

	glm::mat4 draw();

public:
	float castTime, damage, size, cooldown, timer;
	bool moveSpell;
	const char* name;
	Player* player;
	Entity object;
	Transform tMat;

private:
	AbstractSpell* spell;
};


class pSpellType : public SpellDecorator
{
public:
	pSpellType(float speed, float size, float timer, float cd);
};