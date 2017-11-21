#include "Player.h"
#include <gtc/matrix_transform.hpp>

#define DEG_TO_RADIAN 0.017453293 //defined in .cpp to prevent redefinition.

Player::Player(glm::vec3 pos)
{
	position = pos;
	rotation = 0.0f;

	player = new GameObject(position);
	player->init();
	eye = glm::vec3(0.0f, 1.0f, 10.0f); // left, up, forward
	at = glm::vec3(0.0f, 1.0f, 3.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}



void Player::update()
{
	player->update();
	//position.y = player->getPosition().y;
	inputHandler();
	at = position;
	eye = moveForward(at, rotation, -10.0f);
	eye.y = position.y + 2;
	collider();
}

////renders the camera
void Player::render()
{
}

glm::mat4 Player::createCam(glm::mat4 camview)
{
	camview = glm::lookAt(eye, at, up);

	return camview;
}

void Player::collider()
{
	//code to collide

}


//// moves the player either forwards or backwards.  
//// First parameter takes the position of the player
//// next is the angle to find where the player is facing
//// followed by a direction of where the player should move
//// anything above 0 will go forward, and less than 0 will move backwards.
glm::vec3 Player::moveForward(glm::vec3 pos, GLfloat angle, GLfloat d)
{
	return glm::vec3(pos.x + d*std::sin(rotation * DEG_TO_RADIAN), pos.y, pos.z - d*std::cos(rotation * DEG_TO_RADIAN));
}

//// moves the player either left or right.  
//// First parameter takes the position of the player
//// next is the angle to find where the player is facing
//// followed by a direction of where the player should move
//// anything above 0 will go right, and less than 0 will move left.
glm::vec3 Player::moveToSide(glm::vec3 pos, GLfloat angle, GLfloat d)
{
	return glm::vec3(pos.x + d*std::cos(rotation * DEG_TO_RADIAN), pos.y, pos.z + d*std::sin(rotation * DEG_TO_RADIAN));
}

////handles keys being pressed.
void Player::inputHandler()
{
	keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W]) position = moveForward(position, rotation, 0.1f);
	if (keys[SDL_SCANCODE_S]) position = moveForward(position, rotation, -0.1f);
	if (keys[SDL_SCANCODE_A]) position = moveToSide(position, rotation, -0.1f);
	if (keys[SDL_SCANCODE_D]) position = moveToSide(position, rotation, 0.1f);

	if (keys[SDL_SCANCODE_COMMA]) rotation -= 1.0f;
	if (keys[SDL_SCANCODE_PERIOD]) rotation += 1.0f;
}