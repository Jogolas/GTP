#include "AttackState.h"
#include "NPC.h"
#include "Player.h"
#include "AISpellDecorator.h"


AttackState::AttackState(AbstractAI* npc)
{
	spells.setupSpell();
}

void AttackState::handle(AbstractAI* npc)
{
	if (chasing) {
		dynamic_cast<NPC*>(npc)->controller.moving = true;
		if(dynamic_cast<NPC*>(npc)->getSpell() != nullptr)
			dynamic_cast<AISpellDecorator*>(dynamic_cast<NPC*>(npc)->getSpell())->abilityFired = false;

		timer -= 100;
	}
	else {
		dynamic_cast<NPC*>(npc)->controller.moving = false;
		if (dynamic_cast<NPC*>(npc)->getSpell() != nullptr)
			dynamic_cast<AISpellDecorator*>(dynamic_cast<NPC*>(npc)->getSpell())->abilityFired = true;

		timer++;
	}

	if (fireProjectile) {
		std::cout << "Firing Projectile at player: " << std::endl;
		spellFired = true;
		fireProjectile = false;
	}


	if (spellFired) {
		// first spell to fire
		if (dynamic_cast<NPC*>(npc)->getSpell() == nullptr) {
			spells.fireSpell(npc, spells.spells[0]);
			dynamic_cast<NPC*>(npc)->getSpell()->setRotation(npc->getRotation());
			dynamic_cast<NPC*>(npc)->getSpell()->setPosition(npc->getPosition());
			std::cout << "Spell Name: " << dynamic_cast<AISpellDecorator*>(dynamic_cast<NPC*>(npc)->getSpell())->name << std::endl;
		}

		// fires after the first spell
		if (abs(timer) == 300.0f && dynamic_cast<NPC*>(npc)->getSpell() == spells.spells[0]) {
			// update the spell rotation so it fires towards the player.
			spells.fireSpell(npc, spells.spells[1]);
			dynamic_cast<NPC*>(npc)->getSpell()->setRotation(npc->getRotation());
			dynamic_cast<NPC*>(npc)->getSpell()->setPosition(npc->getPosition());
			std::cout << "Spell Name: " << dynamic_cast<AISpellDecorator*>(dynamic_cast<NPC*>(npc)->getSpell())->name << std::endl;
		}

		//fires after the second spell
		if (abs(timer) == 600.0f && dynamic_cast<NPC*>(npc)->getSpell() == spells.spells[1]) {
			// update the spell rotation so it fires towards the player.
			spells.fireSpell(npc, spells.spells[2]);
			dynamic_cast<NPC*>(npc)->getSpell()->setRotation(npc->getRotation());
			dynamic_cast<NPC*>(npc)->getSpell()->setPosition(npc->getPosition());
			std::cout << "Spell Name: " << dynamic_cast<AISpellDecorator*>(dynamic_cast<NPC*>(npc)->getSpell())->name << std::endl;
		}


		// if the npc has set up a spell, handle it appropriately.
		if (dynamic_cast<NPC*>(npc)->getSpell() != nullptr) {
			dynamic_cast<NPC*>(npc)->getSpell()->handleSpell(npc, dynamic_cast<NPC*>(npc)->controller.getTarget());
		}
	}


	if (timer >= 1000) {
		chasing = true;
		spellFired = false;
		dynamic_cast<NPC*>(npc)->setSpell(nullptr);
	}
	else if (timer <= 1) {
		chasing = false;
		fireProjectile = true;
	}
}