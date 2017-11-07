#include <SDL_ttf.h>
#include "glm.hpp"

#include <vector>

class Renderer
{
public:
	stack<glm::mat4> mvStack;
	Renderer();
	~Renderer();
	void setUpWindow(SDL_Window * window);
	void renderObject(GLuint texture, GLuint object, GLuint indexCount, glm::vec3 position, GLuint shader, glm::vec3 size);
	void renderFBX();
private:
};
