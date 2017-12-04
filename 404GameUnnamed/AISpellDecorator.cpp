#include "AISpellDecorator.h"

////AI SPELL DECORATOR CLASS
glm::mat4 AISpellDecorator::draw()
{

	return glm::mat4(1.0);
}

AISpellDecorator::AISpellDecorator(AbstractAI* npc)
{
	this->npc = npc;
}

AISpellDecorator::~AISpellDecorator()
{
	delete this;
}

void AISpellDecorator::nameAbility(const char* name)
{
	this->name = name;
}

void AISpellDecorator::createCooldown(float cooldown)
{
	cd = cooldown;
}

void AISpellDecorator::setDamage(float dmg)
{
	this->dmg = dmg;
}
////END OF AI SPELL DECORATOR CLASS



////ELEMENT CLASS
Element::Element(AbstractAI* decoration, const char* name, float cooldown, float dmg) : AISpellDecorator(decoration)
{
	AISpellDecorator::createCooldown(cooldown);
	AISpellDecorator::nameAbility(name);
	AISpellDecorator::setDamage(dmg);
}

Element::~Element()
{
	/////
}

glm::mat4 Element::draw()
{
	return AISpellDecorator::draw();
}
////END OF ELEMENT CLASS



////BURNING CLASS
Burning::Burning(AbstractAI* decoration) : AISpellDecorator(decoration)
{

}

Burning::~Burning()
{
	/////
}

glm::mat4 Burning::draw()
{
	return AISpellDecorator::draw();
}
////END OF BURNING CLASS



////POISON CLASS
Poison::Poison(AbstractAI* decoration) : AISpellDecorator(decoration)
{

}

Poison::~Poison()
{
	/////
}

glm::mat4 Poison::draw()
{
	return AISpellDecorator::draw();
}
////END OF POISON CLASS



////FROZEN CLASS
Frozen::Frozen(AbstractAI* decoration) : AISpellDecorator(decoration)
{

}

Frozen::~Frozen()
{
	/////
}

glm::mat4 Frozen::draw()
{
	return AISpellDecorator::draw();
}
////END OF FROZEN CLASS