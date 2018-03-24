#pragma once
#include "CollisionHandler.h"
#include "DrawableObject.h"
#include "Camera.h"


class Player
{
public:
	Player() {}
	Player(glm::vec3 pos);
	void update();
	glm::mat4 draw();

	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 pos) { return position = pos; }

	Collider* getColObject() { return colObj; }

	DrawableObject* getDrawingObject() { return d_object; }

	glm::vec3 getEye() { return eye; }
	glm::vec3 getAt() { return at; }
	glm::vec3 getUp() { return up; }

	GLfloat getRotation() { return rotation; }
	GLfloat setRotation(GLfloat rot) { return rotation = rot; }

public:
	Camera cam;

private:
	//methods
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 moveToSide(glm::vec3 pos, GLfloat angle, GLfloat d);
	void inputHandler();

	Collider* colObj;
	DrawableObject* d_object;
	GLuint health = 100;

	glm::vec3 position;
	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;

	GLfloat rotation;
	const Uint8 *keys;
	GLuint mouse;

	GLuint lastMouseX;
	GLuint lastMouseY;
};