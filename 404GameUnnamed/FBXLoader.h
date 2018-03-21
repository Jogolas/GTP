#pragma once
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class FBXLoader
{
public:
	FBXLoader() {}
	FBXLoader(char *name) {	loadModel(name); }
	void Draw(GLuint shader);
private:
	std::vector<Texture> textures_loaded;	
	std::vector<Mesh> meshes;
	std::string directory;
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};