#include "Player.h"

#define DEG_TO_RADIAN 0.017453293 //defined in .cpp to prevent redefinition.

Player::Player(glm::vec3 pos)
{
	position = pos;
	rotation = 0.0f;
}

void Player::init()
{
	std::vector<GLfloat> verts, norms, texCoords;
	std::vector<GLuint> indices;
	Renderer::loadObj("bunny-5000.obj", verts, norms, texCoords, indices);
	GLuint size = indices.size(), indexCount = size;
	model = Renderer::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), nullptr, indexCount, indices.data());
}

void Player::update()
{
	inputHandler();

	collider();
}

void Player::render(const GLuint shader)
{
	//code to draw
	/*Renderer::setObjLightPos(shader, glm::value_ptr(tmp));
	Renderer::setObjMatrix(shader, "projection", glm::value_ptr(projection));
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(-25.0f + i + i * 4, -0.8f, 0.0f));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(20.0f, 20.0f, 20.0f));
	Renderer::setObjMatrix(shader, "modelView", glm::value_ptr(mvStack.top()));
	Renderer::setObjMaterial(shader, material);
	Renderer::drawObj(model, indexCount, GL_TRIANGLES);*/
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
}