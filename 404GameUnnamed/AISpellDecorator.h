#pragma once
#include "AbstractAI.h"

class AISpellDecorator : public AbstractAI
{
public:
	AISpellDecorator(AbstractAI* npc);
	virtual ~AISpellDecorator();
	glm::mat4 draw();

	float getCooldown() { return cd; }
	float cooldownTimer(float timer)
	{ 
		if(timer <= 0) timer--;
		return timer;
	}
	float getDamage() { return dmg; }
	bool getAbility() { return ablitiyUsed; }
	const char* getName() { return name; }

private:
	AbstractAI* npc;
	float cd, dmg;
	bool ablitiyUsed;
	const char* name;

protected:
	void nameAbility(const char* name);
	void createCooldown(float cooldown);
	void setDamage(float dmg);
};


class Element : public AISpellDecorator
{
public:
	Element(AbstractAI* decoration, const char* name, float cooldown, float dmg);
	~Element();
	glm::mat4 draw();
};


class Burning : public AISpellDecorator
{
public:
	Burning(AbstractAI* decoration);
	~Burning();
	glm::mat4 draw();
};


class Poison : public AISpellDecorator
{
public:
	Poison(AbstractAI* decoration);
	~Poison();
	glm::mat4 draw();
};

class Frozen : public AISpellDecorator
{
public:
	Frozen(AbstractAI* decoration);
	~Frozen();
	glm::mat4 draw();
};