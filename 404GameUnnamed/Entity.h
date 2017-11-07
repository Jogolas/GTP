#pragma once
class Collider;

class Entity
{
public:
	virtual void update() = 0;
	virtual vec3 getPosition() = 0;
	virtual vec3 setPosition(vec3 position) = 0;
	virtual const AABB* const getAABB() = 0;
	virtual void init() = 0;
	virtual Collider* getCollider() = 0;
};