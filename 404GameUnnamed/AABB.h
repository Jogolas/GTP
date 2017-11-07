// Based on the work of Marco Gilardi's from IPM
#pragma once
#include "Collider.h"
#include "Utils.h"
#include "CollisionDetection.h"

class AABB : public Collider
{
public:
	AABB(glm::vec3& radius, const Transform& transform) : radius(radius), centre(transform.getPosition()) {};
	virtual ~AABB() {};

	bool isColliding(Collider* const collider);
	void update(const Transform& transform);

	CollisionDetection* getContact() const;
	glm::vec3 getRadius() const;
	glm::vec3 getCentre() const;

private:
	std::vector<glm::vec3> contactPoints() const;
	glm::vec3 contactNormal() const;

	glm::vec3 radius;
	glm::vec3 centre;
	Collider* collider;
};