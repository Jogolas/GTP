#pragma once
#include <glm.hpp>
#include <gtc\constants.hpp>
// #include <GL\glut.h> why glut?
#include <iostream>
#include "GravityForce.h"
#include "AABB.h"
#include "Mesh.h"

class GameObject : public Entity 
{
public:
	GameObject();
	GameObject(glm::vec3 iposition);
	virtual ~GameObject() { delete collider; };

	float getMass();
	float getInverseMass() { return inverseMass; }
	float getHeight() { return height; }
	float getWidth() { return width; }
	float getLength() { return length; }
	float getRotation() { return xRotate; }

	glm::vec3 applyGravity();
	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 position) { return this->position = position; }
	glm::vec3 getCenter();
	glm::vec3 addForce(const glm::vec3& force);
	glm::vec3 setVelocity(glm::vec3 vel) { velocity = vel; return velocity; }
	glm::vec3 getVelocity() { return velocity; }
	glm::vec3 getSize(float x, float y, float z);

	Collider* getCollider() { return collider; }
	const AABB* const getAABB() { return nullptr; } // not supported.

	void clearAccumilator();
	void init();
	void update();
	void update(float dt);

private:
	Transform transform;
	Collider* collider;

	float mass;
	float inverseMass = 1 / getMass();
	float height;
	float width;
	float length;
	float xRotate;

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 forceAccum;
	glm::vec3 force;
	glm::vec3 centre;
	glm::vec3 size;
	
	const glm::vec3 downForce = { 0.0f, -0.15f, 0.0f };
	GravityForce grav = GravityForce(downForce);
	
	void EulerSolver(float dt);
	void verletSolver(float dt);
};