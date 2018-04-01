#include "AISpellDecorator.h"

//// AISpellDecorator Class
AISpellDecorator::AISpellDecorator(AbstractAISpell* spell, AbstractAI* npc)
{
	this->npc = npc;
	this->spell = spell;
	damage = 100.0f;
	colObj = new Colliable(position, glm::vec3(0.2, 0.2, 0.2));
}

AISpellDecorator::~AISpellDecorator()
{
	std::cout << "removed " << name << std::endl;
	abilityFired = false;
}

glm::vec3 moveSpell(glm::vec3 pos, float d, float angle)
{
	return glm::vec3(pos.x + d * std::sin(angle), pos.y, pos.z - d * std::cos(angle)); // using the bosses angle, so radians have already been set
}

void AISpellDecorator::handleSpell(Player* target)
{
	if (!abilityFired) {
		position = npc->getPosition();
		rotation = npc->getRotation();
	}
	else 
		position = moveSpell(position, 0.29, rotation);

	colObj->setPosition(position);
	colObj->setRotation(rotation);

	if (cd.CollisionAgainstBox(colObj, target->getColObject())) {
		colObj->setPosition(glm::vec3(-100.0f)); // throwing the col box away outside as a temp measure.
		position = colObj->getPosition();
		target->removeHealth(damage);
	}
}


//// SpellType class
SpellType::SpellType(const char* name, float inidmg)
{
	AISpellDecorator::abilityName(name);
	AISpellDecorator::abilityDmg(inidmg);
}

SpellType::~SpellType()
{
	//AISpellDecorator::~AISpellDecorator();
}

void SpellType::handleSpell(Player* target)
{
	AISpellDecorator::handleSpell(target);
}


//// SpellEffect Class
SpellEffect::SpellEffect()
{

}

SpellEffect::~SpellEffect()
{
	//AISpellDecorator::~AISpellDecorator();
}

void SpellEffect::handleSpell(Player* target)
{
	AISpellDecorator::handleSpell(target);
}