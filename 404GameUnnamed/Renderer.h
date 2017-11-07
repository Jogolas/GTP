#include <SDL_ttf.h>
#include "glm.hpp"
#include "GL\glew.h"
#include <vector>

class Renderer
{
public:
	Renderer();
	~Renderer();
	glm::mat4 modelview;
	void setUpWindow(SDL_Window * window);
	void renderObject(GLuint texture, GLuint object, GLuint indexCount, glm::vec3 position, GLuint shader, glm::vec3 size);
	void renderFBX();
private:
};
