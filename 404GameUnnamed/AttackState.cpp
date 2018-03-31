#include "AttackState.h"
#include "NPC.h"
#include "Player.h"


void AttackState::handle(AbstractAI* npc)
{
	if (chasing) {
		dynamic_cast<NPC*>(npc)->controller.moving = true;
		//timer--;
	}
	else {
		dynamic_cast<NPC*>(npc)->controller.moving = false;
		timer++;
	}

	if (fireProjectile) {
		std::cout << "Firing Projectile at player" << std::endl;
	}

	if (timer >= 500) {
		chasing = true;
		fireProjectile = false;
	}
	else if (timer <= 1) {
		chasing = false;
		fireProjectile = true;
	}
}