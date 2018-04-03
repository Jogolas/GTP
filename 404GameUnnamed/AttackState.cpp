#include "AttackState.h"
#include "NPC.h"
#include "Player.h"
#include "AISpellDecorator.h"


void AttackState::handle(AbstractAI* npc)
{
	if (chasing) {
		dynamic_cast<NPC*>(npc)->controller.moving = true;
		timer -= 100;
	}
	else {
		dynamic_cast<NPC*>(npc)->controller.moving = false;
		timer++;
	}

	if (fireProjectile) {
		std::cout << "Firing Projectile at player: " << std::endl;
		spellFired = true;
		fireProjectile = false;
	}


	if (spellFired) {
		dynamic_cast<AISpellDecorator*>(dynamic_cast<NPC*>(npc)->getSpell())->velocity = 1.0f;
		dynamic_cast<NPC*>(npc)->getSpell()->handleSpell(dynamic_cast<NPC*>(npc)->controller.getTarget());
		if (abs(timer) == 150.0f) {
			dynamic_cast<NPC*>(npc)->getSpell()->setRotation(npc->getRotation());
			dynamic_cast<NPC*>(npc)->getSpell()->setPosition(npc->getPosition());
		}
		else if (abs(timer) == 300.0f) {
			dynamic_cast<NPC*>(npc)->getSpell()->setRotation(npc->getRotation());
			dynamic_cast<NPC*>(npc)->getSpell()->setPosition(npc->getPosition());
		}
	}

	if (timer >= 500) {
		chasing = true;
		spellFired = false;
	}
	else if (timer <= 1) {
		chasing = false;
		fireProjectile = true;
	}
}