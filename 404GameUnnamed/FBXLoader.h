#pragma once
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "assimp\mesh.h"
#include "assimp\texture.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	aiString path;
};

class FBXLoader
{
public:
	FBXLoader(char *name) {	loadModel(name); }
	void Draw(GLuint shader);
private:
	std::vector<Mesh> meshes;
	std::string directory;
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);	
};