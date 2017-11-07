#include <SDL_ttf.h>
#include "glm.hpp"
#include "GL\glew.h"
#include <vector>
#include "rt3D.h"
#include "rt3DObjLoader.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	GLuint mesh;
	//sets up the data for the object
	std::vector<GLfloat> verts;
	std::vector<GLfloat> norms;
	std::vector<GLfloat> tex_coords;
	std::vector<GLuint> indices;
	GLuint size = indices.size();
	GLuint meshIndexCount = size;

	void renderObject(const char* object);
	void renderFBX(const char* fbx);
	void draw(glm::mat4 stack, GLuint texture, glm::vec3 position, GLuint shader);

private:
};
