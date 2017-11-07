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

vec3 GameObject::getCenter()
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

GameObject::GameObject(vec3 position)
{
	this->position = position;
	vec3 iVelocity(0, 0, 0);
	this->velocity = iVelocity;
}

vec3 GameObject::applyGravity()
{
	if (position.y > 0)
	{
		position += downForce;
		return position;
	}
}

vec3 GameObject::addForce(const vec3& force)
{
	forceAccum += force;
	return forceAccum;
}

void GameObject::clearAccumilator()
{
	forceAccum = vec3(0.0f, 0.0f, 0.0f);
}

void GameObject::init()
{
	transform.Translate(vec3(50, 0, 0));
	collider = new AABB(vec3(getWidth(), getHeight(), getLength()), transform);
}

Collider* GameObject::getCollider()
{
	return collider;
}

void GameObject::update(float dt)
{
	
	grav.updateForce(this, dt);
	collider->update(transform);
}

GameObject::GameObject()
{
	init();
}