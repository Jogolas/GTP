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
		if (mouse & SDL_BUTTON(SDL_BUTTON_RIGHT))
			player->setRotation(player->cam.angView.y);



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

};