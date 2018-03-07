#pragma once
#include "glm.hpp"

class AABB
{
//// Based on the work of Marco Gilardi's from IPM
//public:
//	AABB() {}
//	AABB(glm::vec3& radius, const Transform& transform) : radius(radius), centre(transform.getPosition()) {};
//	virtual ~AABB() {};
//
//	bool isColliding(Collider* const c);
//	void update(const Transform& transform);
//
//	CollisionDetection* getContact() const;
//	glm::vec3 getRadius() const;
//	glm::vec3 getCentre() const;
//
//private:
//	std::vector<glm::vec3> contactPoints() const;
//	glm::vec3 contactNormal() const;
//
//	glm::vec3 radius;
//	glm::vec3 centre;
//	Collider* collider;


//getting to the point of no return here, if its not working now a working version is getting created, regardless if its good or bad.
public:
	AABB operator+(const glm::vec3& p) const
	{
		AABB result = (*this);
		result.vecMin = p + vecMin;
		result.vecMax = p + vecMax;

		return result;
	}

	glm::vec3 vecMin;
	glm::vec3 vecMax;
};
