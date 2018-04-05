#include "Player.h"
#include "D_Object.h"
#include <cmath>

Player::Player(glm::vec3 pos)
{
	position = pos;
	rotation = 0.0f;

	d_object = new D_Object();
	colObj = new Colliable(position, glm::vec3(1, 1, 1));

	cam = Camera(eye = glm::vec3(0.0f, 1.0f, 5.0f)); // left, up, forward
	at = glm::vec3(0.0f, 1.0f, 3.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	health = 100.0f;
}

void Player::update()
{

	float camRotX = cam.angView.y;
	float camRotY = cam.angView.p;

	inputHandler();

	at = glm::vec3(position.x, position.y + 1, position.z);

	//auto camX.y = glm::vec3(camX.x, -5.0f * std::sin(glm::radians(camRotY)), camX.z);

	cam.Position = moveToSide(at, camRotX, -5.0);
	cam.Position.y = position.y + (-5.0f * std::sin(glm::radians(camRotY))) + 1;

	colObj->setPosition(position);
	colObj->setRotation(rotation);
}


glm::mat4 Player::draw()
{
	glm::mat4 model(1.0);

	model = glm::translate(model, position);
	//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(-rotation), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(0.5f));


	//d_object->resetMatrix();
	//d_object->Translation();
	//d_object->Rotation();
	//d_object->Scaled();

	return model;
}


//// moves the player either forwards or backwards.  
//// First parameter takes the position of the player
//// next is the angle to find where the player is facing
//// followed by a direction of where the player should move
//// anything above 0 will go forward, and less than 0 will move backwards.
glm::vec3 Player::moveForward(glm::vec3 pos, GLfloat angle, GLfloat d)
{
	return glm::vec3(pos.x + d*std::sin(glm::radians(angle)), pos.y, pos.z - d*std::cos(glm::radians(angle)));
}

//// moves the player either left or right.  
//// First parameter takes the position of the player
//// next is the angle to find where the player is facing
//// followed by a direction of where the player should move
//// anything above 0 will go right, and less than 0 will move left.
glm::vec3 Player::moveToSide(glm::vec3 pos, GLfloat angle, GLfloat d)
{
	return glm::vec3(pos.x + d*std::cos(glm::radians(angle)), pos.y, pos.z + d*std::sin(glm::radians(angle)));
}

////handles keys being pressed.
void Player::inputHandler()
{
	keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_W]) position = moveToSide(position, rotation, 0.3f);
	if (keys[SDL_SCANCODE_S]) position = moveToSide(position, rotation, -0.3f);
	if (keys[SDL_SCANCODE_A]) position = moveForward(position, rotation, 0.3f);
	if (keys[SDL_SCANCODE_D]) position = moveForward(position, rotation,  -0.3f);
}