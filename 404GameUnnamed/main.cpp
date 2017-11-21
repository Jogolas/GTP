////brings up console window
#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif


#include "Graph.h"
#include "Renderer.h"
#include <iostream>
#include <stack>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Player.h"

Player* p1 = new Player(glm::vec3(0, 0, 0));
#define DEG_TO_RADIAN 0.017453293
GLuint shader, skyBox, rabbit, cube, indexCount = 0, skybox;
std::stack<glm::mat4> mvStack;

Renderer::lightStruct light = {
	{ 0.3f, 0.3f, 0.3f, 1.0f }, // ambient
	{ 1.0f, 1.0f, 1.0f, 1.0f }, // diffuse
	{ 1.0f, 1.0f, 1.0f, 1.0f }, // specular
	{ 10.0f, 10.0f, 10.0f, 1.0f }  // position
};

glm::vec4 lightPos(-10.0f, 2.0f, 15.0f, 1.0f); //light position

Renderer::materialStruct material = {
	{ 0.2f, 0.4f, 0.2f, 1.0f }, // ambient
	{ 0.5f, 1.0f, 0.5f, 1.0f }, // diffuse
	{ 0.0f, 0.1f, 0.0f, 1.0f }, // specular
	2.0f  // shininess
};

void init()
{
	shader = Renderer::initiliaseShader("phong-tex.vert", "phong-tex.frag");
	Renderer::setObjLight(shader, light);
	Renderer::setObjMaterial(shader, material);
	skyBox = Renderer::initiliaseShader("cubeMap.vert", "cubeMap.frag");

	std::vector<GLfloat> verts, norms, texCoords;
	std::vector<GLuint> indices;

	Renderer::loadObj("bunny-5000.obj", verts, norms, texCoords, indices);
	GLuint size = indices.size();
	indexCount = size;
	rabbit = Renderer::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), nullptr, indexCount, indices.data());

	verts.clear();
	norms.clear();
	texCoords.clear();
	indices.clear();

	Renderer::loadObj("cube.obj", verts, norms, texCoords, indices);
	size = indices.size();
	indexCount - size;
	skybox = Renderer::bitMapLoader("sky.bmp");
	cube = Renderer::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), nullptr, indexCount, indices.data());


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void update()
{
	p1->update();
}

void draw(SDL_Window * window)
{
	// clear the screen
	glEnable(GL_CULL_FACE);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 150.0f);

	GLfloat scale(1.0f); // just to allow easy scaling of complete scene

	glm::mat4 modelview(1.0); // set base position for scene
	mvStack.push(modelview);

	GLuint uniformIndex = glGetUniformLocation(shader, "modelView");
	glUniform3fv(uniformIndex, 1, glm::value_ptr(modelview));

	//skybox
	glUseProgram(skyBox);
	Renderer::setObjMatrix(shader, "projection", glm::value_ptr(projection));

	glDepthMask(GL_FALSE); // make sure writing to update depth test is off
	glm::mat3 mvRotOnlyMat3 = glm::mat3(mvStack.top());
	mvStack.push(glm::mat4(mvRotOnlyMat3));

	glCullFace(GL_FRONT); // drawing inside of cube!
	glBindTexture(GL_TEXTURE_2D, skybox);
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(1.5f, 1.5f, 1.5f));
	Renderer::setObjMatrix(shader, "modelview", glm::value_ptr(mvStack.top()));
	Renderer::drawObj(cube, indexCount, GL_TRIANGLES);
	mvStack.pop();
	glCullFace(GL_BACK); // drawing inside of cube!

	// back to remainder of rendering
	glDepthMask(GL_TRUE); // make sure depth test is on

	glUseProgram(shader);
	Renderer::setObjMatrix(shader, "projection", glm::value_ptr(projection));

	glm::vec4 tmp = mvStack.top()*lightPos;
	light.position[0] = tmp.x;
	light.position[1] = tmp.y;
	light.position[2] = tmp.z;
	Renderer::setObjLightPos(shader, glm::value_ptr(tmp));

	glBindTexture(GL_TEXTURE_2D, skybox);
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(-10.0f, -0.1f, -10.0f));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(20.0f, 0.1f, 20.0f));
	Renderer::setObjMatrix(shader, "modelview", glm::value_ptr(mvStack.top()));
	Renderer::setObjMaterial(shader, material);
	Renderer::drawObj(cube, indexCount, GL_TRIANGLES);
	mvStack.pop();

	//draws all the toon shaded, alternate toon shaded, and metallic toon shaded bunnies
	for (int i = 0; i < 7; i++)
	{
		glUseProgram(shader);
		//draw a toon shaded rabbit for the first row
		Renderer::setObjLightPos(shader, glm::value_ptr(tmp));
		Renderer::setObjMatrix(shader, "projection", glm::value_ptr(projection));
		mvStack.push(mvStack.top());
		mvStack.top() = glm::translate(mvStack.top(), glm::vec3(-25.0f + i + i * 4, -0.8f, 0.0f));
		mvStack.top() = glm::scale(mvStack.top(), glm::vec3(20.0f, 20.0f, 20.0f));
		Renderer::setObjMatrix(shader, "modelView", glm::value_ptr(mvStack.top()));
		Renderer::setObjMaterial(shader, material);
		Renderer::drawObj(rabbit, indexCount, GL_TRIANGLES);
		mvStack.pop();
	}

	p1->render();

	// remember to use at least one pop operation per push...
	mvStack.pop(); // initial matrix
	glDepthMask(GL_TRUE);

	SDL_GL_SwapWindow(window); // swap buffers
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