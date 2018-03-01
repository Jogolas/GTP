#pragma once
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"

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