#include "glm.hpp"
#include "Renderer.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(glm::vec3 pos);
	GLuint model;
	void pInit();
	void pUpdate();
	void render(const GLuint shader);

	glm::vec3 getPPosition() { return getPosition(); }
	glm::vec3 setPPosition(glm::vec3 pos) { return setPosition(pos); }


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