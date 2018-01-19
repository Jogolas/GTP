// Based on the work of Marco Gilardi's from IPM
#pragma once
#include "glm.hpp"
#include <vector>

class CollisionDetection
{
public:
	CollisionDetection(std::vector<glm::vec3>& contactPoints, glm::vec3 normal) : pointsOfContact(contactPoints),
		contactNormal(normal) {};
	virtual ~CollisionDetection() {};

	std::vector<glm::vec3> getContactPoints() const { return pointsOfContact; }
	glm::vec3 getCollisionNormal() const { return contactNormal; }

private:
	std::vector<glm::vec3> pointsOfContact;
	glm::vec3 contactNormal;
};