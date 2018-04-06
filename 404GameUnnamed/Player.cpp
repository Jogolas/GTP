#include "Player.h"
#include "D_Object.h"
#include <cmath>

Player::Player(glm::vec3 pos)
{
	d_object = new D_Object();

	cam = Camera(glm::vec3(0.0f, 1.0f, 5.0f)); // left, up, forward

	health = 1000.0f;

	g_object.setup(new Colliable(pos, glm::vec3(1, 1, 1)), pos, 0.3f, 0);
}

void Player::update()
{
	float camRotY = cam.angView.p;

	auto at = g_object;
	at.angle = cam.angView.y;
	at.position.y += 1.0f;

	cam.Position = tMat.moveToSide(at, -5.0f);
	cam.Position.y = g_object.position.y + (-5.0f * std::sin(glm::radians(camRotY))) + 1;

	g_object.colObj->setPosition(g_object.position);
	g_object.colObj->setRotation(g_object.angle);
}


glm::mat4 Player::draw()
{
	glm::mat4 model(1.0);

	model = glm::translate(model, g_object.position);
	//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(-g_object.angle), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(0.5f));

	//d_object->resetMatrix();
	//d_object->Translation();
	//d_object->Rotation();
	//d_object->Scaled();

	return model;
}