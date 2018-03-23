#ifndef EANGLE_H
#define EANGLE_H

#include "glm.hpp"

class EAngle
{
public:
	EAngle()
	{
		p = y = r = 0;
	}


	EAngle(float pitch, float yaw, float roll)
	{
		p = pitch;
		y = yaw;
		r = roll;
	}

	glm::vec3 ToVector() const;
	void Normalize();

public:
	float p;
	float y;
	float r;
};


#endif // !