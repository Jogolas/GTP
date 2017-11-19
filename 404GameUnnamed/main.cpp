////brings up console window
#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif


#include "Graph.h"
#include "Renderer.h"
#include <iostream>
#include "Player.h"

Player* p1 = new Player(glm::vec3(0, 0, 0));

void update()
{
	p1->update();
}

void draw(SDL_Window * window)
{

}

void init()
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
	}

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(hWindow);
	SDL_Quit();
	return 0;
}