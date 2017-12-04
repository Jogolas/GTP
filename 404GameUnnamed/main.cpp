////brings up console window
#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#define DEG_TO_RADIANS 0.017453293

#include "NPC.h"
#include <iostream>
#include "Player.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <stack>
#include "rt3d.h"
#include "rt3dObjLoader.h"

AbstractAI* boss = new NPC(glm::vec3(0.0f, 2.0f, 0.0f));
Player* p1 = new Player(glm::vec3(5, 1, 4));

////Some Globals for testerino
GLuint shaderProgram;
GLuint meshIndexCount = 0;

GLuint meshObjects[1];
GLuint textures[1];

std::stack<glm::mat4> mvStack;

rt3d::lightStruct light0 = {
	{ 0.4f, 0.4f, 0.4f, 1.0f }, // ambient
	{ 1.0f, 1.0f, 1.0f, 1.0f }, // diffuse
	{ 1.0f, 1.0f, 1.0f, 1.0f }, // specular
	{ -5.0f, 2.0f, 2.0f, 1.0f }  // position
};

glm::vec4 lightPos(0.0f, 10.0f, 0.0f, 1.0f); //light position

// light attenuation
GLfloat attConstant = 0.05f;
GLfloat attLinear = 0.0f;
GLfloat attQuadratic = 0.0f;


rt3d::materialStruct material0 = {
	{ 0.4f, 0.4f, 0.4f, 1.0f }, // ambient
	{ 0.4f, 0.4f, 0.4f, 1.0f }, // diffuse
	{ 0.2f, 0.2f, 0.2f, 1.0f }, // specular
	2.0f  // shininess
};

// A simple texture loading function
// lots of room for improvement - and better error checking!
GLuint loadBitmap(char *fname) {
	GLuint texID;
	glGenTextures(1, &texID); // generate texture ID

							  // load file - using core SDL library
	SDL_Surface *tmpSurface;
	tmpSurface = SDL_LoadBMP(fname);
	if (!tmpSurface) {
		std::cout << "Error loading bitmap" << std::endl;
	}

	// bind texture and set parameters
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	SDL_PixelFormat *format = tmpSurface->format;

	GLuint externalFormat, internalFormat;
	if (format->Amask) {
		internalFormat = GL_RGBA;
		externalFormat = (format->Rmask < format->Bmask) ? GL_RGBA : GL_BGRA;
	}
	else {
		internalFormat = GL_RGB;
		externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tmpSurface->w, tmpSurface->h, 0,
		externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(tmpSurface); // texture loaded, free the temporary buffer
	return texID;	// return value of texture ID
}


void update()
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	p1->update();

	if (keys[SDL_SCANCODE_1]) 
		dynamic_cast<NPC*>(boss)->getController()->setTarget(p1->getPlayer());
	

	dynamic_cast<NPC*>(boss)->update();

	glm::vec3 distance = dynamic_cast<NPC*>(boss)->getPosition() - p1->getPosition();

	if (glm::length(distance) > 10) p1->findRotation(dynamic_cast<NPC*>(boss)->getPosition());
}

void draw(SDL_Window * window)
{
	glEnable(GL_CULL_FACE);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f * DEG_TO_RADIANS), 800.0f / 600.0f, 1.0f, 150.0f);


	glm::mat4 modelview(1.0);

	mvStack.push(modelview);
	mvStack.top() = p1->createCam(mvStack.top());

	glm::vec4 tmp = mvStack.top() * lightPos;
	light0.position[0] = tmp.x;
	light0.position[1] = tmp.y;
	light0.position[2] = tmp.z;


	// draw a small cube around light position to see how light moves
	glUseProgram(shaderProgram);
	glBindTexture(GL_TEXTURE_2D, textures[0]); // studded steel texture
	mvStack.push(mvStack.top());
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));
	////set up the light
	rt3d::setLight(shaderProgram, light0);
	rt3d::setMaterial(shaderProgram, material0);
	rt3d::setLightPos(shaderProgram, glm::value_ptr(tmp));

	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(0.0f, 0.0f, 0.0f));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(20.0f, 0.1f, 20.0f));
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
	mvStack.pop();

	////boss cube
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(dynamic_cast<NPC*>(boss)->getPosition()));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(1.0f, 2.0f, 1.0f));
	mvStack.top() = glm::rotate(mvStack.top(), float(dynamic_cast<NPC*>(boss)->getController()->getRotation()), glm::vec3(0, 1, 0));
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
	mvStack.pop();


	////player cube
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(p1->getPosition()));
	//mvStack.top() = glm::scale(mvStack.top(), glm::vec3(1.0f, 1.0f, 1.0f));
	mvStack.top() = glm::rotate(mvStack.top(), float((-90 + p1->getRotation()) * DEG_TO_RADIANS), glm::vec3(0, 1, 0));
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
	mvStack.pop();


	glBindTexture(GL_TEXTURE_2D, 0);

	

	mvStack.pop();//initial matrix

	glDepthMask(GL_TRUE);

	SDL_GL_SwapWindow(window);
}


void init()
{

	shaderProgram = rt3d::initShaders("phong-tex.vert", "phong-tex.frag");
	//shaderProgram = Renderer::initiliseShaders("toonShader.vert", "toonShader.frag");
	rt3d::setLight(shaderProgram, light0);
	rt3d::setMaterial(shaderProgram, material0);
	// set light attenuation shader uniforms
	GLuint uniformIndex = glGetUniformLocation(shaderProgram, "attConst");
	glUniform1f(uniformIndex, attConstant);
	uniformIndex = glGetUniformLocation(shaderProgram, "attLinear");
	glUniform1f(uniformIndex, attLinear);
	uniformIndex = glGetUniformLocation(shaderProgram, "attQuadratic");
	glUniform1f(uniformIndex, attQuadratic);


	std::vector<GLfloat> verts;
	std::vector<GLfloat> norms;
	std::vector<GLfloat> tex_coords;
	std::vector<GLuint> indices;

	rt3d::loadObj("cube.obj", verts, norms, tex_coords, indices);
	meshIndexCount = indices.size();
	textures[0] = loadBitmap("studdedmetal.bmp");
	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), meshIndexCount, indices.data());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}




int main(int argc, char *argv[])
{
	SDL_Window * hWindow; // handles windows.
	SDL_GLContext glContext;
	hWindow = Renderer::createWindow(glContext);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cout << "glewInit failed, aborting." << std::endl;
		exit(1);
	}
	std::cout << glGetString(GL_VERSION) << std::endl;

	init();

	bool running = true;
	SDL_Event sdlEvent;
	while (running) {
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_QUIT) running = false;
		}

		update();
		draw(hWindow);
	}


	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(hWindow);
	SDL_Quit();
	return 0;
}