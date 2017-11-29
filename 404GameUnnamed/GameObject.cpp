#include "GameObject.h"


void GameObject::EulerSolver(float dt)
{
	position = position + dt * velocity;
	velocity = velocity + dt * acceleration;
}

void GameObject::verletSolver(float dt)
{
	GameObject::getMass();

	position = (position + (dt * velocity)) + (0.5f * (dt *dt)) * acceleration;
	velocity = velocity + 0.5f * dt * acceleration;

	acceleration.x = acceleration.x / mass;
	acceleration.y = acceleration.y / mass;

	velocity = velocity + 0.5f *dt * acceleration;
}

float GameObject::getMass()
{
	if ((acceleration.x > 0 || acceleration.y > 0 || acceleration.z > 0) 
		|| (force.x > 0 || force.y > 0 || force.y > 0))
	{
		mass = force.y / acceleration.y;
	}
	return mass;
}

glm::vec3 GameObject::getCenter()
{
	centre.x = width / 2;
	centre.y = height / 2;
	centre.z = length / 2;

	return centre;
}

GameObject::GameObject()
{
	init();
}

GameObject::GameObject(glm::vec3 position)
{
	this->position = position;
	glm::vec3 iVelocity(0, 0, 0);
	this->velocity = iVelocity;
	init();
}

glm::vec3 GameObject::applyGravity()
{
	if (position.y > 0)
	{
		position += downForce;
		return position;
	}

	return position;
}

glm::vec3 GameObject::addForce(const glm::vec3& force)
{
	forceAccum += force;
	return forceAccum;
}

void GameObject::clearAccumilator()
{
	forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);
}

void GameObject::init()
{
	transform.Translate(glm::vec3(50, 50, 50));
	collider = new AABB(glm::vec3(getWidth(), getHeight(), getLength()), transform);
}

void GameObject::update(float dt)
{
	
	grav.updateForce(this, dt);
	collider->update(transform);
}