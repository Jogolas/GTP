//Based off of Marco Gilardi's work from IPM
#include "Transform.h"
#include <iostream>
using namespace std;

// The assumption for this class is that we are not attaching the game object to any hierachy so the coordinates are always expressed directly in world coordinates
Transform::Transform()
{
	// The first column of the transformation matrix matches the direction of the local x axis of the object expressed with respect to the world reference system in homogeneous coords
	// The second column of the transformation matrix matches the direction of the local y axis of the object expressed with respect to the world reference system in homogeneous coords
	// The third column of the transformation matrix contains the position of the object expressed with respect to the world reference system in homogeneous coords
	transformMatrix = mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);//Identity matrix
								//inputs are done by column (i.e. the matrix is transposed)
}

// Translate the object by creating a Translation matrix and 
// multiplying it to the transform matrix
void Transform::Translate(const vec3& translation)
{
	mat4 translationMatrix = mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translation.x, translation.y, translation.z, 1.0f);//<-- This last row is usually omitted in optimised code
														   //	  because it is always constant (they use 2x3 matrices), 
														   //    but as this code is didactic I left it here to help 
														   //	  you match the code with the theory in the lectures

	transformMatrix = translationMatrix * transformMatrix;
}

// Scale the object by creating a Scaling matrix and 
// multiplying it to the transform matrix
void Transform::Scale(const vec3& scaling)
{
	mat4 scalingMatrix = mat4(scaling.x, 0.0f, 0.0f, 0.0f,
		0.0f, scaling.y, 0.0f, 0.0f,
		0.0f, 0.0f, scaling.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f); //<-- Row omitted in optimised code

	transformMatrix = scalingMatrix * transformMatrix;
}

// Rotate the object around its X local axis by creating a Rotation matrix and 
// multiplying it to the transform matrix
void Transform::RotateX(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	mat4 rotateMatrix = mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, c, s, 0.0f,
		0.0f, -s, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f); //<-- Row omitted in Optimised code

	transformMatrix = rotateMatrix * transformMatrix;
}

// Rotate the object around its Y local axis by creating a Rotation matrix and 
// multiplying it to the transform matrix
void Transform::RotateY(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	mat4 rotateMatrix = mat4(c, 0.0f, s, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-s, 0.0f, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f); //<-- Row omitted in Optimised code

	transformMatrix = rotateMatrix * transformMatrix;
}

// Rotate the object around its Z local axis by creating a Rotation matrix and 
// multiplying it to the transform matrix
void Transform::RotateZ(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	mat4 rotateMatrix = mat4(c, s, 0.0f, 0.0f,
		-s, c, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f); //<-- Row omitted in Optimised code

	transformMatrix = rotateMatrix * transformMatrix;
}


vec3 Transform::getPosition() const
{
	vec4 col3 = column(transformMatrix, 3);
	return vec3(col3.x, col3.y, col3.z); // The third column of the transformation matrix contains the position of the object in homogeneous coords
}

vec3 Transform::getScale() const
{
	float sx = length(column(transformMatrix, 0)); // It measures the length of the local x axis
	float sy = length(column(transformMatrix, 1)); // It measures the length of the local y axis
	float sz = length(column(transformMatrix, 2)); // It measures the length of the local y axis
	return vec3(sx, sy, sz);
}

vec3 Transform::getOrientation() const
{

	vec4 col0 = normalize(column(transformMatrix, 0)); // By normalising the x axis whe get the cosine (in the first component of the vector)
													   // and sine (in the second component of the vector) of the angle by which the object is rotated
	return vec3(col0.x, col0.y, col0.z);
}

// This gives the y axis of the object expressed in world coordinates
vec3 Transform::getVerticalDirection() const
{
	vec4 col1 = column(transformMatrix, 1);
	return vec3(col1.x, col1.y, col1.z); // y Axis
}

// This gives the x axis of the object expressed in world coordinates
vec3 Transform::getHorizontalDirection() const
{
	vec4 col0 = column(transformMatrix, 0);
	return vec3(col0.x, col0.y, col0.z); // x Axis
}

vec3 Transform::getFrontDircetion() const
{
	vec4 col2 = column(transformMatrix, 2);
	return vec3(col2.x, col2.y, col2.z); // z Axis
}

mat4 Transform::worldToLocalMatrix()
{
	return transformMatrix; //This matrix transforms world coordinates into local coordinates (if we are not using any hierarchical data structure)
}

mat4 Transform::localToWorldMatrix()
{
	return inverse(transformMatrix);
}