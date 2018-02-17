#pragma once
#include "Renderer.h"

class menu
{
public:
	menu();

	void drawMenu();

private:
	const Uint8* keys;
	GLuint textures[1];
};