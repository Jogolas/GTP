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
			player->g_object.position = player->tMat.moveToSide(player->g_object, player->g_object.velocity * 0.66f);
			player->g_object.position = player->tMat.moveForward(player->g_object, player->g_object.velocity * 0.66f);
		}
		else if (keys[SDL_SCANCODE_W] && keys[SDL_SCANCODE_E]) {
			player->g_object.position = player->tMat.moveToSide(player->g_object, player->g_object.velocity * 0.66f);
			player->g_object.position = player->tMat.moveForward(player->g_object, -player->g_object.velocity * 0.66f);
		}
		else if (keys[SDL_SCANCODE_W])
			player->g_object.position = player->tMat.moveToSide(player->g_object, player->g_object.velocity);
		else if (keys[SDL_SCANCODE_Q])
			player->g_object.position = player->tMat.moveForward(player->g_object, player->g_object.velocity);
		else if (keys[SDL_SCANCODE_E])
			player->g_object.position = player->tMat.moveForward(player->g_object, -player->g_object.velocity);
		else if (keys[SDL_SCANCODE_S]) 
			player->g_object.position = player->tMat.moveToSide(player->g_object, -player->g_object.velocity);




		// rotates the player
		if (keys[SDL_SCANCODE_A])
			player->g_object.angle -= 1.0f;
		if (keys[SDL_SCANCODE_D])
			player->g_object.angle += 1.0f;
	}
};