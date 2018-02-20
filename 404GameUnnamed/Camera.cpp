#include "camera.h"
#include "gtc/matrix_transform.hpp"

#define DEG_TO_RADIAN 0.017453293

glm::mat4 Camera::draw(glm::mat4 camView, Player* player)
{
	camView = glm::lookAt(glm::vec3(player->getEye().x, player->getEye().y+2.5, player->getEye().z),
			  glm::vec3(player->getAt().x, player->getAt().y+1, player->getAt().z),
		      glm::vec3(player->getUp().x, player->getUp().y, player->getUp().z));
	return camView;
}