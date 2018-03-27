#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "Shader.h"

#include "glm.hpp"
#include "gtc\matrix_transform.hpp"

#include "stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
public:
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;

	Model() {}
	// constructor, expects a filepath to a 3D model
	Model(std::string const &path, bool gamma = false) : gammaCorrection(gamma)
	{	
		loadModel(path);
	}

	void Draw(Shader shader);
	void DrawMesh(Shader shader);


private:
	void loadModel(std::string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif