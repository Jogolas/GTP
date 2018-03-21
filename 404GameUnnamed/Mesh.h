#pragma once
#include "Renderer.h"
#include "glm.hpp"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>


struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	Mesh() {}
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	{
		this->Vertices = vertices;
		this->Indices = indices;
		this->Textures = textures;
	}
	GLuint createMesh(GLuint meshID, const char* filename);
	//GLuint Mesh::createMesh(unsigned num_verts, GLfloat *verts, std::vector<GLfloat> norms, std::vector<GLfloat> tex_coords, std::vector<GLuint> indices);
	GLuint getIndexCount() { return indexCount; }
	GLuint getMeshID() { return meshIndex; }
	glm::mat4 meshTranslation(glm::mat4 modelMatrix, glm::vec3 position);
	glm::mat4 meshScaling(glm::mat4 modelMatrix, glm::vec3 scale);
	glm::mat4 meshRotation(glm::mat4 modelMatrix, GLfloat roation, glm::vec3 rotate);
	void drawMesh(GLuint meshID);
	void drawFBXMesh(GLuint shader);

private:
	GLuint indexCount;
	GLuint meshIndex;
	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;
	std::vector<Texture> Textures;
};
