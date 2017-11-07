#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <GL\glut.h>
#include <iostream>
#include "GravityForce.h"
#include "Entity.h"
#include "Transform.h"
#include "AABB.h"

using namespace glm;
using namespace std;

class GameObject : public Entity 
{
public:
	GameObject();
	GameObject(vec3 iposition);
	virtual ~GameObject() { delete collider; };

	float getMass();
	float getInverseMass() { return inverseMass; }
	float getHeight() { return height; }
	float getWidth() { return width; }
	float getLength() { return length; }
	float getRotation() { return xRotate; }

	vec3 applyGravity();
	vec3 getPosition() { return position; }
	vec3 setPosition(vec3 position) { return this->position = position; }
	vec3 getCenter();
	vec3 addForce(const vec3& force);
	vec3 setVelocity(vec3 vel) { velocity = vel; return velocity; }
	vec3 getVelocity() { return velocity; }

	Collider* getCollider() { return collider; }

	void clearAccumilator();
	void init();
	void update(float dt);

private:
	Transform transform;
	Collider* collider;

	float mass;
	float inverseMass = 1 / mass;
	float height;
	float width;
	float length;
	float xRotate;

	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	vec3 forceAccum;
	vec3 force;
	vec3 centre;
	
	const vec3 downForce = { 0.0f, -0.15f, 0.0f };
	GravityForce grav = GravityForce(downForce);
	
	void EulerSolver(float dt);
	void verletSolver(float dt);
};