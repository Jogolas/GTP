#ifndef CAMERA_H
#define CAMERA_H

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"

#include "EAngle.h"

#include <vector>

//Defines several possible options for camera movement.
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

//default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.3f;
const float ZOOM = 45.0f;


class Camera
{
public:
	//camera attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	//Euler Angles
	EAngle angView;

	//camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;



	//Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
		: Front(glm::vec3(0.0f, 0.0f, 1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		angView.y = yaw;
		angView.p = pitch;
		updateCameraVectors();
	}

	//Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		angView.y = yaw;
		angView.p = pitch;
		updateCameraVectors();
	}

	//Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	//Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		updateCameraVectors();

		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
		{
			Position -= Right * velocity;
			angView.y -= Position.y;
		}
		if (direction == RIGHT)
		{
			Position += Right * velocity;
			angView.y += Position.y;
		}

		updateCameraVectors();
		GetViewMatrix();
	}

	//Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
	{

		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		angView.y += xoffset;
		angView.p += yoffset;

		//// Make sure that when pitch is out of bounds, screen doesn't get flipped
		angView.Normalize();

		////Update Front, Right and Up vectors using the updated Euler Angles
		updateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}


private:
	//Calculates the front vector from the Camera's Euler Angles
	void updateCameraVectors()
	{
		//Calculate the new Front vector
		glm::vec3 front = angView.ToVector();
		Front = glm::normalize(front);

		// Also re-calculate the Right and Up vector
		//Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement
		Right = glm::normalize(glm::cross(Front, WorldUp)); 
		Up = glm::normalize(glm::cross(Right, Front));
	}
};

#endif