#include "SpellDecorator.h"

SpellDecorator::SpellDecorator()
{

}


SpellDecorator::SpellDecorator(Player* p, const char* name, float dmg, float speed, float size, float timer, float cd) : name(name), damage(dmg), size(size), castTime(timer), cooldown(cd)
{
	this->object.setup(new Colliable(glm::vec3(-100.0f), glm::vec3(size)), glm::vec3(-100), speed, 0.0f);
	player = p;
	this->timer = 0.0f;
}

void SpellDecorator::handleSpell()
{
	if (this->timer <= 0) {
		moveSpell = false;

		timer = cooldown;
	}


	if (moveSpell) {
		if (timer == cooldown) {
			object.position = player->g_object.position;
			object.angle = player->g_object.angle;
		}

		timer--;
		object.position = tMat.moveToSide(object, object.velocity);
	}
	else {
		object.position = glm::vec3(-100);
	}

	object.colObj->setPosition(object.position);
}

glm::mat4 SpellDecorator::draw()
{
	glm::mat4 model(1.0);
	model = glm::translate(model, object.position);
	model = glm::rotate(model, object.angle, glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(size));

	return model;
}

pSpellType::pSpellType(float speed, float size, float timer, float cd)
{
	this->castTime = timer;
	this->size = size;
	this->cooldown = cd;
	this->object.setup(new Colliable(glm::vec3(-100.0f), glm::vec3(size)), glm::vec3(-100), speed, 0.0f);
}