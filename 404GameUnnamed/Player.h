#include "glm.hpp"
#include "Renderer.h"
#include "GameObject.h"

class Player
{
public:
	Player(glm::vec3 pos);
	void update();
	glm::mat4 draw(glm::mat4 modelmatrix);
	void findRotation(glm::vec3 tar);

	glm::mat4 createCam(glm::mat4 camview);
	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 pos) { return position = pos; }

	Entity* getPlayer() { return player; }

	GLfloat getRotation() { return rotation; }

private:
	//methods
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 moveToSide(glm::vec3 pos, GLfloat angle, GLfloat d);
	void inputHandler();
	void collider();

	//variables
	Entity* player;

	glm::vec3 position;
	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;
	GLfloat rotation;
	const Uint8 *keys;
};