////brings up console window
#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#include "Renderer.h"
#include <iostream>
#include <stack>
#include "Scene.h"


void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

bool update(Scene* game)
{
	return game->updateScene();
}


void draw(SDL_Window * window, Scene* game)
{
	// clear the screen
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	game->drawScene();

	SDL_GL_SwapWindow(window); // swap buffers
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

	Scene* scene = new Scene(true);
	init();

	bool running = true;
	SDL_Event sdlEvent;
	while (running) {
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_QUIT) running = false;

			if (sdlEvent.type == SDL_KEYDOWN)
			{
				if(sdlEvent.key.repeat == 0)
					if(sdlEvent.key.keysym.scancode == SDL_SCANCODE_0)
						Renderer::toggleFullScreen();
			}
		}



		Renderer::setFullScreen(hWindow);

		running = update(scene);
		draw(hWindow, scene);
		Renderer::setFullScreen(hWindow);
	}

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(hWindow);
	SDL_Quit();
	return 0;
}