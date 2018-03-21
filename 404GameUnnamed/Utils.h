//// Based on the Utils class by Marco Gilardi's, used in IPM
//#pragma once
//#include "glm.hpp"
//
//class AABB;
//
//class Utils
//{
//public:
//	static const glm::vec3 up;
//	static const glm::vec3 down;
//	static const glm::vec3 left;
//	static const glm::vec3 right;
//	static const glm::vec3 front;
//	static const glm::vec3 back;
//
//	static float DistanceBetweenPoints(const glm::vec3& p1, const glm::vec3& p2);
//	static float DistanceBetweenPointAndPlane(const glm::vec3& p1, const glm::vec3& p2, float d);
//	static char computePointMask(const glm::vec3& p1, const AABB* const aabb);
//	static glm::vec3 projectPointOnAABB(const glm::vec3& p1, const AABB* const aabb);
//	static bool PointIsAbovePlane(const glm::vec3& p1, const glm::vec3& p3, float p4);
//	static glm::vec3 projectPointOnPlane(const glm::vec3& p1, const glm::vec3& p3, float p4);
//
//	Utils() {}
//};