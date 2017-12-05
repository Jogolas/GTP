////brings up console window
#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif


#include "Graph.h"
#include "Renderer.h"
#include <iostream>
#include <stack>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Player.h"
#include "Scene.h"

#define DEG_TO_RADIAN 0.017453293

void init()
{
	
}

void update()
{
	
}

void draw(SDL_Window * window)
{
	
}

int main(int argc, char *argv[])
{
	SDL_Window * hWindow; // handles windows.
	SDL_GLContext glContext;
	hWindow = Renderer::createWindow(glContext);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cout << "glewInit failed, aborting." << std::endl;
		exit(1);
	}
	std::cout << glGetString(GL_VERSION) << std::endl;

	init();

	bool running = true;
	SDL_Event sdlEvent;
	while (running) {
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_QUIT) running = false;
		}

		update();
		draw(hWindow);
		//Renderer::toggleFullScreen(hWindow);
	}

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(hWindow);
	SDL_Quit();
	return 0;
}