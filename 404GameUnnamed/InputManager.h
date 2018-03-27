#pragma once
#include "Camera.h"
#include "SDL.h"

struct MouseHandler
{
	void getMousePosition()
	{
		mouse = SDL_GetMouseState(&x, &y);
	}

	void MouseMotion(Player* player)
	{
		getMousePosition();

		int xoffset = x - lastMouseX;
		int yoffset = lastMouseY - y;

		if (mouse && SDL_BUTTON(SDL_BUTTON_LEFT))
			player->cam.ProcessMouseMovement(xoffset, yoffset);

		lastMouseX = x;
		lastMouseY = y;
	}

	unsigned int mouse;
	int x, y;
	int lastMouseX, lastMouseY;
};