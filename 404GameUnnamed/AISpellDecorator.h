#ifndef AISPELLDECORATOR_H
#define AISPELLDECORATOR_H

#include "AbstractAISpell.h"
#include "CollisionHandler.h"

class AISpellDecorator : public AbstractAISpell
{
public:
	AISpellDecorator() {}
	AISpellDecorator(AbstractAISpell* spell, AbstractAI* npc);
	~AISpellDecorator();

	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 pos) { return position = pos; }

	float getRotation() { return rotation; }
	float setRotation(float rot) { return rotation = rot; }

	virtual void handleSpell(Player* target);
	float spellDamage(float dmg) { return damage += dmg; }


	bool abilityFired = false;
	const char* name;

	float velocity;
private:
	AbstractAISpell* spell;

protected:
	float damage; //allow subclasses to change this variable.
	Collider* colObj;
	CollisionData cd;

	AbstractAI* npc;

	glm::vec3 position;
	float rotation;

	void abilityName(const char* name) { this->name = name; }
	void abilityDmg(float dmg) { this->damage += dmg; }
};


class SpellType : public AISpellDecorator
{
public:
	SpellType( const char* name, float spellIniDmg);
	~SpellType();

	void handleSpell(Player* target);
	float spellDamage(float dmg) { return damage += dmg; }
};


class SpellEffect : public AISpellDecorator
{
public:
	SpellEffect();
	~SpellEffect();

	void handleSpell(Player* target);
	float spellDamage(float dmg) { return damage += dmg; }
};

#endif // !AISPELLDECORATOR_H
