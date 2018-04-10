#pragma once
#include "Camera.h"
#include "SDL.h"

struct MouseHandler
{
	void getMousePosition()
	{
		mouse = SDL_GetMouseState(&x, &y);
	}

	// tracks the mouse position uses the mouse to change the view of the camera.
	void MouseMotion(Player* player)
	{
		// first find the mouse position on the screen.
		getMousePosition();

		// create offsets, inversed y co-ord since the screen goes co-ords go from bottom to top.
		int xoffset = x - lastMouseX;
		int yoffset = lastMouseY - y;

		// when the mouse is pressed, update the camera's view with respect to the offsets
		if (mouse & SDL_BUTTON(SDL_BUTTON_LEFT)) 
			player->cam.ProcessMouseMovement(xoffset, yoffset);
		else if (mouse & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			player->cam.ProcessMouseMovement(xoffset, yoffset);
			player->g_object.angle = player->cam.angView.y;
		} 


		// record the last position of the mouse.
		lastMouseX = x;
		lastMouseY = y;
	}

	unsigned int mouse;
	int x, y;
	int lastMouseX, lastMouseY;
};



struct KeyboardHandler
{
	void handlePlayerkeyboard(Player* player)
	{
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		// player movements
		if (keys[SDL_SCANCODE_W] && keys[SDL_SCANCODE_Q]) {
			player->g_object.velocity = 0.3f * 0.5f;
			player->g_object.position = player->tMat.moveToSide(player->g_object, player->g_object.velocity);
			player->g_object.position = player->tMat.moveForward(player->g_object, player->g_object.velocity);
		}
		else if (keys[SDL_SCANCODE_W] && keys[SDL_SCANCODE_E]) {
			player->g_object.velocity = 0.3f * 0.5f;
			player->g_object.position = player->tMat.moveToSide(player->g_object, player->g_object.velocity);
			player->g_object.position = player->tMat.moveForward(player->g_object, -player->g_object.velocity);
		}
		else if (keys[SDL_SCANCODE_W]) {
			player->g_object.velocity = 0.3f;
			player->g_object.position = player->tMat.moveToSide(player->g_object, player->g_object.velocity);
		}
		else if (keys[SDL_SCANCODE_Q]) {
			player->g_object.velocity = 0.15f;
			player->g_object.position = player->tMat.moveForward(player->g_object, player->g_object.velocity);
		}
		else if (keys[SDL_SCANCODE_E]) {
			player->g_object.velocity = 0.15f;
			player->g_object.position = player->tMat.moveForward(player->g_object, -player->g_object.velocity);
		}
		else if (keys[SDL_SCANCODE_S]) {
			player->g_object.velocity = 0.15f;
			player->g_object.position = player->tMat.moveToSide(player->g_object, -player->g_object.velocity);
		}

		
		// rotates the player
		if (keys[SDL_SCANCODE_A])
		{
			player->cam.ProcessKeyboard(LEFT, 1);
			player->g_object.angle = player->cam.angView.y;
		}
		if (keys[SDL_SCANCODE_D])
		{
			player->cam.ProcessKeyboard(RIGHT, 1);
			player->g_object.angle = player->cam.angView.y;
		}

		// makes the player jump
		if (keys[SDL_SCANCODE_SPACE] && player->grounded == true)
		{
			do
			{
				player->grounded = false;
				player->g_object.velocity += 0.5f;
				player->g_object.position = player->tMat.moveUp(player->g_object, -player->g_object.velocity);
			} while (player->g_object.velocity <= 2.0f  && player->grounded == false);
		}
	}
};