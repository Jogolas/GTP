#pragma once
#include "AbstractAI.h"

////incorrect setup, (WIP)
class AISpellDecorator : public AbstractAI
{
public:
	AISpellDecorator(AbstractAI* npc);
	virtual ~AISpellDecorator();
	glm::mat4 draw();

	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 pos) { return position = pos; }

	void fireForward(AbstractAI* ai, glm::vec3 tar);
	void returnToCenter() {} //dummy

	float getDamage() { return dmg; }
	float cooldownTimer(float timer)
	{ 
		if(timer <= 0) timer--;
		return timer;
	}

	bool getAbility() { return ablitiyUsed; }

	const char* getName() { return name; }

private:
	AbstractAI* npc;
	float dmg;
	bool ablitiyUsed;
	const char* name;
	glm::vec3 position;

protected:
	void nameAbility(const char* name);
	void createCooldown(float cooldown);
	void setDamage(float dmg);
};


class Element : public AISpellDecorator
{
public:
	Element(AbstractAI* decoration, const char* name, float dmg);
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