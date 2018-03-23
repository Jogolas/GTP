#include "Player.h"
#include "D_Object.h"
#include <cmath>

#define DEG_TO_RADIAN 0.017453293 //defined in .cpp to prevent redefinition.

Player::Player(glm::vec3 pos)
{
	position = pos;
	rotation = 0.0f;

	d_object = new D_Object();
	colObj = new Colliable(position, glm::vec3(1, 1, 1));
	eye = glm::vec3(0.0f, 1.0f, 5.0f); // left, up, forward
	at = glm::vec3(0.0f, 1.0f, 3.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Player::~Player()
{
	delete this;
}

void Player::update()
{
	inputHandler();
	at = position;
	eye = moveForward(at, rotation, -5.0f);

	colObj->setPosition(position);
	colObj->setRotation(rotation);
}


glm::mat4 Player::draw(glm::mat4 modelmatrix, glm::vec3 scale)
{
	d_object->setPosition(position);
	d_object->setScale(scale);
	d_object->setFloatRotation(rotation);
	d_object->setVectorRotation(glm::vec3(0, -1, 0));

	return modelmatrix = d_object->draw(modelmatrix);
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
	if (keys[SDL_SCANCODE_W]) position = moveForward(position, rotation, 0.3f);
	if (keys[SDL_SCANCODE_S]) position = moveForward(position, rotation, -0.3f);
	if (keys[SDL_SCANCODE_A]) position = moveToSide(position, rotation, -0.3f);
	if (keys[SDL_SCANCODE_D]) position = moveToSide(position, rotation, 0.3f);

	if (keys[SDL_SCANCODE_E]) at.y += 0.1f;
	if (keys[SDL_SCANCODE_R]) at.y -= 0.1f;

	if (keys[SDL_SCANCODE_H])
	{
		std::cout << health << std::endl;
	}

	if (keys[SDL_SCANCODE_G])
	{
		health -= 1;
		std::cout << health << std::endl;
	}

	if (keys[SDL_SCANCODE_J])
	{
		std::cout << "Health was " << health << std::endl;
		health *= 1.03;
		std::cout << "Health is now " << health << std::endl;
	}

	mouseMotion(x, y);
}

void Player::mouseMotion(GLuint x, GLuint y)
{
	int mouseMovedX = x - lastMouseX;
	int mouseMovedY = y - lastMouseY;

	float sensitivity = 0.5;

	//// the angView.y call is to find out the yaw.
	//// do not mistake for the y-axis.
	if (mouse && SDL_BUTTON(SDL_BUTTON_LEFT)) {

		//angView.p += mouseMovedY * sensitivity;
		angView.y += mouseMovedX * sensitivity;
	}

	angView.Normalize();
	rotation = angView.y;

	lastMouseX = x;
	lastMouseY = y;
}