#include "Renderer.h"
#include "rt3D.h"

void Renderer::setUpWindow(SDL_Window * window) //this method creates a window
{
	SDL_Window * window;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize video
		rt3d::exitFatalError("Unable to initialize SDL");

	// Request an OpenGL 3.0 context.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  // double buffering on
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 8 bit alpha buffering
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // Turn on x4 multisampling anti-aliasing (MSAA)

													   // Create 800x600 window
	window = SDL_CreateWindow("Our Game with no Name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) // Check window was created OK
		rt3d::exitFatalError("Unable to create window");

	context = SDL_GL_CreateContext(window); // Create opengl context and attach to window
	SDL_GL_SetSwapInterval(1); // set swap buffers to sync with monitor's vertical refresh rate
	return window;
}

void Renderer::renderObject(GLuint texture, GLuint object, GLuint indexCount, glm::vec3 position,
	GLuint shader, glm::vec3 size, GLuint material) //this method will render an object with the passed in varaibles
{
	//draws the specified object
	glUseProgram(shader); //applies the passed in shader
	glBindTexture(GL_TEXTURE_2D, texture); //binds the passed in texture
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), position); //sets it to the passed in position
	mvStack.top() = glm::scale(mvStack.top(), size); //renders the object to the desired size
	rt3d::setUniformMatrix4fv(shader, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::setMaterial(shader, material); //renders the object with the correct material
	rt3d::drawIndexedMesh(object, indexCount, GL_TRIANGLES);
	mvStack.pop();
}

void Renderer::renderFBX() //will render the FBX models we use
{

}