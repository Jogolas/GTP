#include "glm.hpp"
#include "Renderer.h"

class Player
{
public:
	Player(glm::vec3 pos);
	void update();
	void render();

	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 pos) { return position = pos; }


private:
	//methods
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 moveToSide(glm::vec3 pos, GLfloat angle, GLfloat d);
	void inputHandler();
	void collider();

	//variables
	glm::vec3 position;
	GLfloat rotation;
	const Uint8 *keys;
};