#include "Renderer.h"

//file reader from previous work since it works
char* Renderer::fileReader(const char *fname, GLint &fSize)
{
	int size;
	char * memblock;

	// file read based on example in cplusplus.com tutorial
	// ios::ate opens file at the end
	std::ifstream file(fname, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open()) {
		size = (int)file.tellg(); // get location of file pointer i.e. file size
		fSize = (GLint)size;
		memblock = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(memblock, size);
		file.close();
		std::cout << "file " << fname << " loaded" << std::endl;
	}
	else {
		std::cout << "Unable to open file " << fname << std::endl;
		fSize = 0;
		// should ideally set a flag or use exception handling
		// so that calling function can decide what to do now
		return nullptr;
	}
	return memblock;
}

//will initialise the shaders for use in other methods
GLuint Renderer::initiliaseShader(const char *vertShader, const char *fragShader)
{

}

//taken from the mains in previous work 
SDL_Window * Renderer::createWindow(SDL_GLContext &context) //pass in a window so the window can be
{		//initialised in one place and called upon again to use in other																	     
		//commands like full screen and resizing
	SDL_Window * window;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize video
	{
		std::cout << "unable to set up window" << std::endl;
	}
	// Request an OpenGL 3.0 context.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  // double buffering on
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 8 bit alpha buffering
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // Turn on x4 multisampling anti-aliasing (MSAA)

	// Create 800x600 window
	window = SDL_CreateWindow("this is da gam", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!window) // Check window was created OK
	{
		std::cout << "unable to set up window" << std::endl;
	}

	context = SDL_GL_CreateContext(window); // Create opengl context and attach to window
	SDL_GL_SetSwapInterval(1); // set swap buffers to sync with monitor's vertical refresh rate
	return window;
}

SDL_Window * Renderer::toggleFullScreen(SDL_Window * window)
{
	//this will toggle between fullscreen and window of whatever resolution it is set to via a key press
	//depending if it's full screen or not
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return window;
}

SDL_Window * Renderer::changeRes(int Width, int Height)
{
	//will change the window size to the one selected from a list most likely
	//probably should be a vector so it's easier to set up and take in
	//like from a list on the menu or something

	return nullptr;
}

void Renderer::loadObj(const char* filename, std::vector<GLfloat> &verts, std::vector<GLfloat> &norms, std::vector<GLfloat> &texcoords, std::vector<GLuint> &indices)
{
	//will load in a specified object file to read from

	////temp stuff by Stephen, Thomas change this in future.
}

void Renderer::setObjProperties(const GLuint shader)
{
	//will set the properties like the light, light position and material used. Maybe also texture will be loaded in here too

	////temp stuff by Stephen, Thomas change this in future.
}

void Renderer::drawObj(const GLuint mesh, const GLuint indexCount, const GLuint primitive)
{
		//will draw a specified object that is loaded in

		////temp stuff by Stephen, Thomas change this in future.
}


//these three will be done later and will be similar to the equivalint object methods
void Renderer::loadFBX()
{

}

void Renderer::setFBXProperties()
{

}

void Renderer::drawFBX()
{

}