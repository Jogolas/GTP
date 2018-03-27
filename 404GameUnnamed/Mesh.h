#ifndef MESH_H
#define MESH_H

#include "glm.hpp"
#include "Shader.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;
	std::vector<Texture> Textures;

	Mesh() {}
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	{
		this->Vertices = vertices;
		this->Indices = indices;
		this->Textures = textures;

		setUpMesh();
	}

	void draw(Shader shader);
	void drawMesh(Shader shader);
	void setUpMesh();
	GLuint VAO;

private:

	GLuint VBO, EBO;
};

#endif