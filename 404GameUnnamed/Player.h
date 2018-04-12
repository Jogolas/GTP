#ifndef PLAYER_H
#define PLAYER_H

#include "CollisionHandler.h"
#include "DrawableObject.h"
#include "Camera.h"
#include "Transform.h"
#include "AbstractSpell.h"


class Player
{
public:
	Player() {}
	Player(glm::vec3 pos);
	void update();
	glm::mat4 draw();
	bool grounded = true;

	DrawableObject* getDrawingObject() { return d_object; }

	float removeHealth(float amount) 
	{ 
		std::cout << "\n Health Before Hit: " << health << std::endl;
		health -= amount; 
		std::cout << "\n Health After Hit: " << health << std::endl;

		return health;
	}

	float getHealth() { return health; }

public:
	Camera cam;
	Entity g_object;
	Transform tMat;
	AbstractSpell* spells[3];
	bool spellFired = false;

private:

	DrawableObject* d_object;
	float health = 100;
	float fov = -5.0f;

	const Uint8 *keys;
	GLuint mouse;


	GLuint lastMouseX;
	GLuint lastMouseY;
};

#endif // !PLAYER_H