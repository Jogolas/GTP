#include "glm.hpp"
#include "Renderer.h"
#include "GameObject.h"

class Player
{
public:
	Player(glm::vec3 pos);
	GLuint model;
	void init();
	void update();
	void render(const GLuint shader);

	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 pos) { return position = pos; }


private:
	//methods
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 moveToSide(glm::vec3 pos, GLfloat angle, GLfloat d);
	void inputHandler();
	void collider();

	//variables
	Entity* player;
	glm::vec3 position;
	GLfloat rotation;
	const Uint8 *keys;
};