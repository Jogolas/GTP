#pragma once
#include "Entity.h"
#include "gtc\matrix_access.hpp"


struct Transform
{
	glm::vec3 moveToSide(Entity object, float d)
	{
		return glm::vec3(object.position.x + (d * std::cos(glm::radians(object.angle))), 
						object.position.y,
						object.position.z + (d * std::sin(glm::radians(object.angle))));
	}

	glm::vec3 moveForward(Entity object, float d)
	{
		return glm::vec3(object.position.x + (d * std::sin(glm::radians(object.angle))),
						object.position.y,
						object.position.z - (d * std::cos(glm::radians(object.angle))));
	}
};