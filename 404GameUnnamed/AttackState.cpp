#include "AttackState.h"
#include "NPC.h"
#include "Player.h"
#include "AISpellDecorator.h"


AttackState::AttackState(AbstractAI* npc)
{
	spells.setupSpell();
	chasing = true;
	fireProjectile = false;
	spellFired = false;
	dynamic_cast<NPC*>(npc)->addSpell(spells.spells[0], 0);
	dynamic_cast<NPC*>(npc)->addSpell(spells.spells[1], 1);
	dynamic_cast<NPC*>(npc)->addSpell(spells.spells[2], 2);
}

void AttackState::handle(AbstractAI* npc)
{
	if (chasing) {
		dynamic_cast<NPC*>(npc)->g_object.velocity += 0.0003f;
		dynamic_cast<NPC*>(npc)->controller.moving = true;

		timer--;
	}
	else {
		dynamic_cast<NPC*>(npc)->g_object.velocity = 0.1f;
		dynamic_cast<NPC*>(npc)->controller.moving = false;

		timer++;
	}

	if (fireProjectile) {
		std::cout << "Firing Projectile at player: " << std::endl;
		spellFired = true;
		fireProjectile = false;
	}


	if (spellFired) {
		// first spell to fire
		if (abs(timer) == 100.0f) {
			dynamic_cast<NPC*>(npc)->getSpell(0)->setRotation(npc->getRotation());
			dynamic_cast<NPC*>(npc)->getSpell(0)->setPosition(npc->getPosition());
			dynamic_cast<NPC*>(npc)->getSpell(0)->setPosition(npc->getPosition());
			dynamic_cast<AISpellDecorator*>(dynamic_cast<NPC*>(npc)->getSpell(0))->abilityFired = true;
			std::cout << "Spell Name: " << dynamic_cast<AISpellDecorator*>(dynamic_cast<NPC*>(npc)->getSpell(0))->name << std::endl;
		}

		// fires after the first spell
		if (abs(timer) == 400.0f) {
			// update the spell rotation so it fires towards the player.
			dynamic_cast<NPC*>(npc)->getSpell(1)->setRotation(npc->getRotation());
			dynamic_cast<NPC*>(npc)->getSpell(1)->setPosition(npc->getPosition());
			dynamic_cast<AISpellDecorator*>(dynamic_cast<NPC*>(npc)->getSpell(1))->abilityFired = true;
			std::cout << "Spell Name: " << dynamic_cast<AISpellDecorator*>(dynamic_cast<NPC*>(npc)->getSpell(1))->name << std::endl;
		}

		//fires after the second spell
		if (abs(timer) == 700.0f) {
			// update the spell rotation so it fires towards the player.
			dynamic_cast<NPC*>(npc)->getSpell(2)->setRotation(npc->getRotation());
			dynamic_cast<NPC*>(npc)->getSpell(2)->setPosition(npc->getPosition());
			dynamic_cast<AISpellDecorator*>(dynamic_cast<NPC*>(npc)->getSpell(2))->abilityFired = true;
			std::cout << "Spell Name: " << dynamic_cast<AISpellDecorator*>(dynamic_cast<NPC*>(npc)->getSpell(2))->name << std::endl;
		}


		// if the npc has set up a spell, handle it appropriately.
		for(int i = 0; i < 3; i++)
			if (dynamic_cast<NPC*>(npc)->getSpell(i) != nullptr) 
				dynamic_cast<NPC*>(npc)->getSpell(i)->handleSpell(npc, dynamic_cast<NPC*>(npc)->controller.getTarget());
	}


	if (timer >= 1000) {
		chasing = true;
		spellFired = false;
	}
	else if (timer <= 1) {
		chasing = false;
		fireProjectile = true;
	}
}