#include "EAngle.h"

glm::vec3 EAngle::ToVector() const
{
	glm::vec3 result;

	result.x = cos(glm::radians(y)) * cos(glm::radians(p));
	result.y = sin(glm::radians(p));
	result.z = sin(glm::radians(y)) * cos(glm::radians(p));

	return result;
}

void EAngle::Normalize()
{
	if (p > 10) p = 10;
	if (p < -35) p = -35;

	while (y < -180)
		y += 360;
	while (y > 180)
		y -= 360;
}