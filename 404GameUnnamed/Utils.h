// Based on the Utils class by Marco Gilardi's, used in IPM
#pragma once
#include <glm\glm.hpp>

using namespace glm;
class AABB;

class Utils
{
public:
	static const vec3 up;
	static const vec3 down;
	static const vec3 left;
	static const vec3 right;
	static const vec3 front;
	static const vec3 back;

	static float DistanceBetweenPoints(const vec3& p1, const vec3& p2);
	static float DistanceBetweenPointAndPlane(const vec3& p1, const vec3& p2, float d);
	static char computePointMask(const vec3& p1, const AABB* const aabb);
	static vec3 projectPointOnAABB(const vec3& p1, const AABB* const aabb);
	static bool PointIsAbovePlane(const vec3& p1, const vec3& p3, float p4);
	static vec3 projectPointOnPlane(const vec3& p1, const vec3& p3, float p4);

private:
	Utils() {};
};