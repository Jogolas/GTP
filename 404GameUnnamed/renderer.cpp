#include "Renderer.h"

//file reader from previous work since it works
char* Renderer::fileReader(const char *fname, GLint &fSize)
{
	int size;
	char * memblock;

	// file read based on example in cplusplus.com tutorial
	// ios::ate opens file at the end
	std::ifstream file(fname, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open()) {
		size = (int)file.tellg(); // get location of file pointer i.e. file size
		fSize = (GLint)size;
		memblock = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(memblock, size);
		file.close();
		std::cout << "file " << fname << " loaded" << std::endl;
	}
	else {
		std::cout << "Unable to open file " << fname << std::endl;
		fSize = 0;
		// should ideally set a flag or use exception handling
		// so that calling function can decide what to do now
		return nullptr;
	}
	return memblock;
}

//will initialise the shaders for use in other methods
GLuint Renderer::initiliaseShader(const char *vertShader, const char *fragShader)
{
	GLuint p, f, v;

	char *vs, *fs;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	// load shaders & get length of each
	GLint vlen;
	GLint flen;
	vs = fileReader(vertShader, vlen);
	fs = fileReader(fragShader, flen);

	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(v, 1, &vv, &vlen);
	glShaderSource(f, 1, &ff, &flen);

	GLint compiled;

	glCompileShader(v);
	glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		std::cout << "Vertex shader not compiled." << std::endl;
	}

	glCompileShader(f);
	glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		std::cout << "Fragment shader not compiled." << std::endl;
	}

	p = glCreateProgram();

	glAttachShader(p, v);
	glAttachShader(p, f);

	glBindAttribLocation(p, VERTEX, "position");
	glBindAttribLocation(p, COLOUR, "color");
	glBindAttribLocation(p, NORMAL, "normal");
	glBindAttribLocation(p, TEXCOORD, "texCoord");

	glLinkProgram(p);
	glUseProgram(p);

	delete[] vs; // dont forget to free allocated memory
	delete[] fs; // we allocated this in the loadFile function...

	return p;
}

//taken from the mains in previous work 
SDL_Window * Renderer::createWindow(SDL_GLContext &context) //pass in a window so the window can be
{																				//initialised in one place and called upon again to use in other
	{																		    //commands like full screen and resizing
		SDL_Window * window;
		if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize video
		{
			std::cout << "unable to set up window" << std::endl;
		}
		// Request an OpenGL 3.0 context.
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  // double buffering on
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 8 bit alpha buffering
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // Turn on x4 multisampling anti-aliasing (MSAA)

														   // Create 800x600 window
		window = SDL_CreateWindow("this is da gam", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		if (!window) // Check window was created OK
		{
			std::cout << "unable to set up window" << std::endl;
		}

		context = SDL_GL_CreateContext(window); // Create opengl context and attach to window
		SDL_GL_SetSwapInterval(1); // set swap buffers to sync with monitor's vertical refresh rate
		return window;
	}
}

void Renderer::toggleFullScreen(SDL_Window * window)
{
	//this will toggle between fullscreen and window of whatever resolution it is set to via a key press
	//depending if it's full screen or not
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

}

void Renderer::changeRes(int Width, int Height)
{
	//will change the window size to the one selected from a list most likely
	//probably should be a vector so it's easier to set up and take in
	//like from a list on the menu or something
	//WINDOW_WIDTH = Width;
	//WINDOW_HEIGHT = Height;
}

void Renderer::loadObj(const char* filename, std::vector<GLfloat> &verts, std::vector<GLfloat> &norms, std::vector<GLfloat> &texcoords, std::vector<GLuint> &indices)
{
	//will load in a specified object file to read from
	GLint fileLength;
	char *fileSource = fileReader(filename, fileLength);

	if (fileLength == 0)
		// should report error here too
		return;

	std::stringstream  fileStream;
	fileStream << fileSource;

	char line[256];
	std::string lineHeader;
	std::string fString1;
	std::string fString2;
	std::string fString3;
	std::stringstream buffer;
	std::vector<position> Verts;
	std::vector<position> Norms;
	std::vector<position> Coords;
	//std::vector<GLint> indexVector;

	GLfloat x, y, z;
	GLint a, b, c;

	int i = 0, iCount = 0;
	position tmp;
	std::map<std::string, GLuint> indexMap;
	int fFormat = FORMAT_UNKNOWN;

	std::cout << "started parsing obj image..." << std::endl;

	while (fileStream.good()) {
		//fileStream.getline(line, 256);
		fileStream >> lineHeader;
		switch (lineHeader[0]) {
		case 'v':
			if (lineHeader.length() > 1)
				switch (lineHeader[1]) {
				case 't':
					fileStream >> tmp.x >> tmp.y;
					Coords.push_back(tmp);
					break;
				case 'n':
					fileStream >> tmp.x >> tmp.y >> tmp.z;
					Norms.push_back(tmp);
					break;
				default:
					break;
				}
			else {
				fileStream >> tmp.x >> tmp.y >> tmp.z;
				Verts.push_back(tmp);
			}
			break;
		case 'f':
			fileStream >> fString1 >> fString2 >> fString3;
			if (!fFormat)
				fFormat = determineFace(fString1);
			if (fFormat > FORMAT_V) {
				addVertex(fString1, indexMap, Verts, Coords, Norms, verts, texcoords, norms, indices, fFormat, iCount);
				addVertex(fString2, indexMap, Verts, Coords, Norms, verts, texcoords, norms, indices, fFormat, iCount);
				addVertex(fString3, indexMap, Verts, Coords, Norms, verts, texcoords, norms, indices, fFormat, iCount);
			}
			else {
				buffer << fString1 << " " << fString2 << " " << fString3;
				buffer >> a >> b >> c;
				buffer.clear();
				indices.push_back(a - 1);
				indices.push_back(b - 1);
				indices.push_back(c - 1);
			}
			break;
		case '#':
			fileStream.getline(line, 256); // ignore line
			break;
		default:
			fileStream.getline(line, 256); // ignore line
		}

	}

	// copy vertex data to output vectors in case only single index was provided....
	if (fFormat == FORMAT_V) {
		for (int v = 0; v < Verts.size(); v++) {
			verts.push_back(Verts[v].x);
			verts.push_back(Verts[v].y);
			verts.push_back(Verts[v].z);
		}
	}

	std::cout << "finished parsing obj image..." << std::endl;
}

void Renderer::setObjProperties(const GLuint shader, lightStruct light, const GLfloat *lightPos, materialStruct material, const char* uniformName, const GLfloat *data)
{
	//will set the properties like the light, light position and material used. Maybe also texture will be loaded in here too
	//pass in the light
	int uniformIndex = glGetUniformLocation(shader, "light.ambient");
	glUniform4fv(uniformIndex, 1, light.ambient);
	uniformIndex = glGetUniformLocation(shader, "light.diffuse");
	glUniform4fv(uniformIndex, 1, light.diffuse);
	uniformIndex = glGetUniformLocation(shader, "light.specular");
	glUniform4fv(uniformIndex, 1, light.specular);
	uniformIndex = glGetUniformLocation(shader, "light.position");
	glUniform4fv(uniformIndex, 1, light.position);

	//pass in light postion
	uniformIndex = glGetUniformLocation(shader, "lightPosition");
	glUniform4fv(uniformIndex, 1, lightPos);

	//pass in the material
	uniformIndex = glGetUniformLocation(shader, "material.ambient");
	glUniform4fv(uniformIndex, 1, material.ambient);
	uniformIndex = glGetUniformLocation(shader, "material.diffuse");
	glUniform4fv(uniformIndex, 1, material.diffuse);
	uniformIndex = glGetUniformLocation(shader, "material.specular");
	glUniform4fv(uniformIndex, 1, material.specular);
	uniformIndex = glGetUniformLocation(shader, "material.shininess");
	glUniform1f(uniformIndex, material.shininess);

	//pass in the matrix
	uniformIndex = glGetUniformLocation(shader, uniformName);
	glUniformMatrix4fv(uniformIndex, 1, GL_FALSE, data);
}

void Renderer::drawObj(const GLuint mesh, const GLuint indexCount, const GLuint primitive)
{
	//will draw a specified object that is loaded in
	glBindVertexArray(mesh);	// Bind mesh VAO
	glDrawElements(primitive, indexCount, GL_UNSIGNED_INT, 0);	// draw VAO 
	glBindVertexArray(0);
}

//these three will be done later and will be similar to the equivalint object methods
void Renderer::loadFBX(const char* filename, std::vector<GLfloat> &verts, std::vector<GLfloat> &norms, std::vector<GLfloat> &texcoords, std::vector<GLuint> &indices)
{
	//will load in a specified object file to read from
	GLint fileLength;
	char *fileSource = fileReader(filename, fileLength);

	if (fileLength == 0)
		// should report error here too
		return;

	std::stringstream  fileStream;
	fileStream << fileSource;

	char line[256];
	std::string lineHeader;
	std::string fString1;
	std::string fString2;
	std::string fString3;
	std::stringstream buffer;
	std::vector<position> Verts;
	std::vector<position> Norms;
	std::vector<position> Coords;
	//std::vector<GLint> indexVector;

	GLfloat x, y, z;
	GLint a, b, c;

	int i = 0, iCount = 0;
	position tmp;
	std::map<std::string, GLuint> indexMap;
	int fFormat = FORMAT_UNKNOWN;

	std::cout << "started parsing fbx image..." << std::endl;

	while (fileStream.good()) {
		//fileStream.getline(line, 256);
		fileStream >> lineHeader;
		switch (lineHeader[0]) {
		case 'v':
			if (lineHeader.length() > 1)
				switch (lineHeader[1]) {
				case 't':
					fileStream >> tmp.x >> tmp.y;
					Coords.push_back(tmp);
					break;
				case 'n':
					fileStream >> tmp.x >> tmp.y >> tmp.z;
					Norms.push_back(tmp);
					break;
				default:
					break;
				}
			else {
				fileStream >> tmp.x >> tmp.y >> tmp.z;
				Verts.push_back(tmp);
			}
			break;
		case 'f':
			fileStream >> fString1 >> fString2 >> fString3;
			if (!fFormat)
				fFormat = determineFace(fString1);
			if (fFormat > FORMAT_V) {
				addVertex(fString1, indexMap, Verts, Coords, Norms, verts, texcoords, norms, indices, fFormat, iCount);
				addVertex(fString2, indexMap, Verts, Coords, Norms, verts, texcoords, norms, indices, fFormat, iCount);
				addVertex(fString3, indexMap, Verts, Coords, Norms, verts, texcoords, norms, indices, fFormat, iCount);
			}
			else {
				buffer << fString1 << " " << fString2 << " " << fString3;
				buffer >> a >> b >> c;
				buffer.clear();
				indices.push_back(a - 1);
				indices.push_back(b - 1);
				indices.push_back(c - 1);
			}
			break;
		case '#':
			fileStream.getline(line, 256); // ignore line
			break;
		default:
			fileStream.getline(line, 256); // ignore line
		}

	}

	// copy vertex data to output vectors in case only single index was provided....
	if (fFormat == FORMAT_V)
	{
		for (int v = 0; v < Verts.size(); v++)
		{
			verts.push_back(Verts[v].x);
			verts.push_back(Verts[v].y);
			verts.push_back(Verts[v].z);
		}
	}

	std::cout << "finished parsing fbx image..." << std::endl;
}

void Renderer::setFBXProperties()
{

}

void Renderer::drawFBX()
{

}

int Renderer::determineFace(std::string string)
{
	unsigned int delim1 = string.find('/');
	if (delim1 == std::string::npos)
		return FORMAT_V;
	unsigned int delim2 = string.rfind('/');
	if (delim1 == delim2)
		return FORMAT_VT;
	if (delim2 == (delim1 + 1))
		return FORMAT_VN;
	return FORMAT_VTN;
}

faceIndex Renderer::getFace(std::string string, int format)
{
	// still need to sort out how to handle v/t properly, as well as v//n
	int delim1 = string.find('/');
	int delim2 = string.rfind('/');

	std::string vstr = string.substr(0, delim1);
	std::stringstream buffer;
	if (format == FORMAT_VT) {
		// v/t format
		std::string tstr = string.substr(delim1 + 1, string.size());
		buffer << vstr << " " << tstr << " " << 0 << " ";
	}
	else {
		// v/t/n format or v//n format
		std::string nstr = string.substr(delim2 + 1, string.size() - delim2);
		if (format == FORMAT_VTN) {
			std::string tstr = string.substr(delim1 + 1, delim2 - (delim1 + 1));
			buffer << vstr << " " << tstr << " " << nstr << " ";
		}
		else
			buffer << vstr << " " << 0 << " " << nstr << " ";
	}

	faceIndex f;
	buffer >> f.v >> f.t >> f.n;
	f.v--; f.t--, f.n--;
	buffer.clear();
	return f;
}

GLuint Renderer::createMesh(const GLuint numVerts, const GLfloat* vertices, const GLfloat* colours, const GLfloat* normals, const GLfloat* texcoords, const GLuint indexCount, const GLuint* indices)
{
	GLuint VAO;
	// generate and set up a VAO for the mesh
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint *pMeshBuffers = new GLuint[5];


	if (vertices == nullptr) {
		// cant create a mesh without vertices... oops
		std::cout << "Attempt to create a mesh with no vertices" << std::endl;
	}

	// generate and set up the VBOs for the data
	GLuint VBO;
	glGenBuffers(1, &VBO);

	// VBO for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 3 * numVerts * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX);
	pMeshBuffers[VERTEX] = VBO;


	// VBO for colour data
	if (colours != nullptr) {
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 3 * numVerts * sizeof(GLfloat), colours, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)COLOUR, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(COLOUR);
		pMeshBuffers[COLOUR] = VBO;
	}

	// VBO for normal data
	if (normals != nullptr) {
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 3 * numVerts * sizeof(GLfloat), normals, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(NORMAL);
		pMeshBuffers[NORMAL] = VBO;
	}

	// VBO for tex-coord data
	if (texcoords != nullptr) {
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 2 * numVerts * sizeof(GLfloat), texcoords, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXCOORD);
		pMeshBuffers[TEXCOORD] = VBO;
	}

	if (indices != nullptr && indexCount > 0) {
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);
		pMeshBuffers[INDEX] = VBO;
	}
	// unbind vertex array
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// return the identifier needed to draw this mesh

	vertexArrayMap.insert(std::pair<GLuint, GLuint *>(VAO, pMeshBuffers));

	return VAO;
}

void Renderer::addVertex(std::string fString, std::map<std::string, GLuint> &indexMap, std::vector<position> &inVerts, std::vector<position> &inCoords, std::vector<position> &inNorms, std::vector<GLfloat> &verts, std::vector<GLfloat> &texcoords, std::vector<GLfloat> &norms, std::vector<GLuint> &indices, int fFormat, int &index)
{

	auto itr = indexMap.find(fString);
	if (itr == indexMap.end())
	{
		faceIndex f = getFace(fString, fFormat);
		verts.push_back(inVerts[f.v].x);
		verts.push_back(inVerts[f.v].y);
		verts.push_back(inVerts[f.v].z);
		if (fFormat < FORMAT_VN)
		{
			texcoords.push_back(inCoords[f.t].x);
			texcoords.push_back(inCoords[f.t].y);
		}
		if (fFormat > FORMAT_VT)
		{
			norms.push_back(inNorms[f.n].x);
			norms.push_back(inNorms[f.n].y);
			norms.push_back(inNorms[f.n].z);
		}
		indexMap.insert(std::pair<std::string, GLuint>(fString, index));
		indices.push_back(index++);
	}
	else
	{
		indices.push_back(itr->second);
	}
}
