#include "Player.h"
#include <gtc/matrix_transform.hpp>
#include "GameObject.h"

#define DEG_TO_RADIAN 0.017453293 //defined in .cpp to prevent redefinition.

Player::Player(glm::vec3 pos)
{
	position = pos;
	rotation = 0.0f;

	player = new GameObject();
	player->init();
	eye = glm::vec3(0.0f, 1.0f, 5.0f); // left, up, forward
	at = glm::vec3(0.0f, 1.0f, 3.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}



void Player::update()
{
	player->update();
	inputHandler();
	at = position;
	eye = moveForward(at, camRot, -5.0f);
	eye.y = position.y + 2;
	collider();

	player->setPosition(position); //update the GameObject position at the end.
}


glm::mat4 Player::draw(glm::mat4 modelmatrix)
{
	modelmatrix = mesh.meshTranslation(modelmatrix, position);
	modelmatrix = mesh.meshScaling(modelmatrix, glm::vec3(1, 1, 1));
	modelmatrix = mesh.meshRotation(modelmatrix, -180 + rotation, glm::vec3(0, -1, 0));

	return modelmatrix;
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
	int x, y;

	keys = SDL_GetKeyboardState(NULL);
	mouse = SDL_GetMouseState(&x, &y);
	if (keys[SDL_SCANCODE_W]) position = moveForward(position, rotation, 0.1f);
	if (keys[SDL_SCANCODE_S]) position = moveForward(position, rotation, -0.1f);
	if (keys[SDL_SCANCODE_A]) position = moveToSide(position, rotation, -0.1f);
	if (keys[SDL_SCANCODE_D]) position = moveToSide(position, rotation, 0.1f);


	mouseMotion(x, y);
}

void Player::mouseMotion(GLuint x, GLuint y)
{
	int tmp = x;
	if (mouse && SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		x = 0;
		rotation = x + tmp;
	}
	else if (mouse && SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		x = 0;
		camRot = x;
	}
}

void Player::findRotation(glm::vec3 tar)
{
	glm::vec3 distance = tar - position;

	if (glm::length(distance) >= 2) {
		rotation = (float)atan2(distance.z, distance.x);
	}
}