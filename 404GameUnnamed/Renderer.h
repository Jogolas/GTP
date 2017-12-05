#pragma once
//code based on the RT3D classes from the Advanced Graphics class and code found here:
//https://sourceforge.net/p/irrext/code/91/tree/trunk/extensions/scene/IMeshLoader/fbx/ and
//https://github.com/BSVino/MathForGameDevelopers/tree/shader-rimlight/renderer

#include <GL/glew.h>
#include <glm.hpp>
#include <SDL.h>
#include <assimp\Importer.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#define FORMAT_UNKNOWN 0
#define FORMAT_V 1
#define FORMAT_VT 2
#define FORMAT_VTN 3
#define FORMAT_VN 4

#define VERTEX		0
#define COLOUR		1
#define NORMAL		2
#define TEXCOORD    3
#define INDEX		4

struct position 
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct faceIndex 
{
	int v;
	int t;
	int n;
};


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace Renderer
{
	struct lightStruct
	{
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat position[4];
	};

	struct materialStruct
	{
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat shininess;
	};

	static std::map<GLuint, GLuint *> vertexArrayMap;

	//based on methods in the RT3D obj loader class
	char* fileReader(const char *fname, GLint &fSize); //loads in needed files
	GLuint initiliaseShader(const char *vertShader, const char *fragShader); //initialises our shaders

	SDL_Window * createWindow(SDL_GLContext &context); //creates a window to render in
	void toggleFullScreen(SDL_Window * window); //toggles full screen
	void changeRes(int width, int height); //changes window resolution to what is resolution is selected

	GLuint bitMapLoader(char *name);

	//obj loader and realted methods
	//based on methods in the RT3D obj loader class
	void loadObj(const char* filename, std::vector<GLfloat> &verts, std::vector<GLfloat> &norms, std::vector<GLfloat> &texcoords, std::vector<GLuint> &indices); //load in object model
	void setLight(const GLuint shader, lightStruct light);
	void setLightPos(const GLuint shader, const GLfloat *lightPos);
	void setMaterial(const GLuint shader, materialStruct material);
	void setMatrix(const GLuint shader, const char* uniformName, const GLfloat *data);
	void drawObj(const GLuint mesh, const GLuint indexCount, const GLuint primitive); //draws the object model

	//FBX loader and related methods
	void loadFBX(const char* filename, std::vector<GLfloat> &verts, std::vector<GLfloat> &norms, std::vector<GLfloat> &texcoords, std::vector<GLuint> &indices); //load in fbx model
	void setFBXProperties(); //set the properties for an fbx model
	void drawFBX(); //draw the fbx model
	

	//based on methods in the RT3D obj loader class
	GLuint createMesh(const GLuint numVerts, const GLfloat* vertices, const GLfloat* colours, const GLfloat* normals, const GLfloat* texcoords, const GLuint indexCount, const GLuint* indices);
	int determineFace(std::string string);
	faceIndex getFace(std::string string, int format);
	void addVertex(std::string fString, std::map<std::string, GLuint> &indexMap, std::vector<position> &inVerts, std::vector<position> &inCoords, std::vector<position> &inNorms, std::vector<GLfloat> &verts, std::vector<GLfloat> &texcoords, std::vector<GLfloat> &norms, std::vector<GLuint> &indices, int fFormat, int &index);
};