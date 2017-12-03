#pragma once
#include "AbstractAI.h"

class AISpellDecorator : public AbstractAI
{
public:
	AISpellDecorator(AbstractAI* npc);
	virtual ~AISpellDecorator();
	glm::mat4 draw();

	float getCooldown() { return cd; }
	bool getAbility() { return ablitiyUsed; }
	const char* getName() { return name; }

private:
	AbstractAI* npc;
	float cd;
	bool ablitiyUsed;
	const char* name;

protected:
	void nameAbility(const char* name);
	void createCooldown(float cooldown);
};


class Element : public AISpellDecorator
{
public:
	Element(AbstractAI* decoration, const char* name, float cooldown);
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