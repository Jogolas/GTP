#include "AISpellDecorator.h"
#include "NPC.h"

////AI SPELL DECORATOR CLASS
AISpellDecorator::AISpellDecorator(AbstractAI* npc)
{
	this->npc = npc;
}

AISpellDecorator::~AISpellDecorator()
{
	delete this;
}

glm::mat4 AISpellDecorator::draw()
{

	return glm::mat4(1.0);
}

void AISpellDecorator::fireForward(AbstractAI* ai, glm::vec3 tar)
{
	glm::vec3 distance = tar - position;
	float angle = dynamic_cast<NPC*>(ai)->getController()->getRotation();

	if (length(distance) > 1) {
		position = glm::vec3(position.x + (0.2f * std::sin(angle)), position.y, position.z - (0.2f * std::cos(angle)));
	}
}

void AISpellDecorator::nameAbility(const char* name)
{
	this->name = name;
}

void AISpellDecorator::setDamage(float dmg)
{
	this->dmg = dmg;
}

////END OF AI SPELL DECORATOR CLASS



////ELEMENT CLASS
Element::Element(AbstractAI* decoration, const char* name, float dmg) : AISpellDecorator(decoration)
{
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