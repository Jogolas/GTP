#include "AISpellDecorator.h"

//// AISpellDecorator Class
AISpellDecorator::AISpellDecorator(AbstractAISpell* spell, glm::vec3 scale)
{
	this->spell = spell;
	this->scale = scale;
	damage += 100.0f + spell->spellDamage(0);
	velocity += 0.0f + dynamic_cast<SpellType*>(spell)->velocity;
	name = dynamic_cast<SpellType*>(spell)->name;
	scale = glm::vec3(1.0f);
	position = glm::vec3(-100);
	colObj = new Colliable(position, this->scale);

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

glm::mat4 AISpellDecorator::draw()
{
	glm::mat4 model(1.0);
	model = glm::translate(model, position);
	model = glm::rotate(model, rotation, glm::vec3(0, 1, 0));
	model = glm::scale(model, scale);

	return model;
}

void AISpellDecorator::handleSpell(AbstractAI* npc, Player* target)
{
	if (abilityFired)
		position = moveSpell(position, velocity, rotation);


	colObj->setPosition(position);
	colObj->setRotation(rotation);

	if (cd.CollisionAgainstBox(colObj, target->g_object.colObj)) {
		colObj->setPosition(glm::vec3(-100.0f)); // throwing the col box away outside as a temp measure.
		position = colObj->getPosition();

		target->removeHealth(damage);
	}
}


//// SpellType class
SpellType::SpellType(const char* name, float inidmg, float speed)
{
	abilityName(name);
	damage += inidmg;
	velocity += speed;
}

SpellType::~SpellType()
{
	//AISpellDecorator::~AISpellDecorator();
}


//// SpellEffect Class
SpellEffect::SpellEffect()
{

}

SpellEffect::~SpellEffect()
{
	//AISpellDecorator::~AISpellDecorator();
}
