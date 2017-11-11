#pragma once

#include <GL/glew.h>
#include <SDL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#define FORMAT_UNKNOWN 0
#define FORMAT_V 1
#define FORMAT_VT 2
#define FORMAT_VTN 3
#define FORMAT_VN 4

using namespace std;

class Renderer
{
public:	
	char* fileReader(const char *fname, GLint &fSize); //loads in needed files
	GLuint initiliaseShader(const char *vertShader, const char *fragShader); //initialises our shaders
	
	SDL_Window * createWindow(SDL_Window * window, SDL_GLContext &context); //creates a window to render in
	SDL_Window * toggleFullScreen(SDL_Window * window); //toggles full screen
	SDL_Window * changeRes(int width, int height); //changes window resolution to what is resolution is selected

	void loadObj(const char* filename, std::vector<GLfloat> &verts, std::vector<GLfloat> &norms, std::vector<GLfloat> &texcoords, std::vector<GLuint> &indices); //load in object model
	void setObjProperties(const GLuint shader); //sets the properties for an object model, might set up something like the light and material structs from rt3D
	void drawObj(const GLuint mesh, const GLuint indexCount, const GLuint primitive); //draws the object model

	void loadFBX(); //load in fbx model
	void setFBXProperties(); //set the properties for an fbx model
	void drawFBX(); //draw the fbx model

private:
	int width = 800, height = 600; //default window size, maybe we'll add in an array of resolutions that you can select from in a menu
};