// Based on the work of Marco Gilardi's from IPM

#pragma once
#include "glm\glm\glm.hpp"
#include <vector>

using namespace std;
using namespace glm;

class CollisionDetection
{
public:
	CollisionDetection(vector<vec3>& contactPoints, vec3 normal) : pointsOfContact(contactPoints),
		contactNormal(normal) {};
	virtual ~CollisionDetection() {};

	vector<vec3> getContactPoints() const { return pointsOfContact; }
	vec3 getCollisionNormal() const { return contactNormal; }

private:
	vector<vec3> pointsOfContact;
	vec3 contactNormal;
};