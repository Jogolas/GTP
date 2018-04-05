#pragma once
#include "glm.hpp"
#include "Collider.h"


struct Entity
{
	glm::vec3 position;
	float velocity, angle;
	Collider* colObj;


	void setup(Collider* co, glm::vec3 pos, float vel, float ang)
	{
		colObj = co;
		position = pos;
		velocity = vel;
		angle = ang;
	}
};