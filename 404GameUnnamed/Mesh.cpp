#include "Mesh.h"
#include <iostream>
#include <vector>
#include "gtc\type_ptr.hpp"
#include "gtc\matrix_transform.hpp"

#define DEG_TO_RADIAN 0.017453293

////Function only supports loading in obj files, meshID is used to create the mesh data, file name is the name of the obj file.
////Function returns the indexCount which are the size of the indices.
GLuint Mesh::createMesh(GLuint meshID, const char* filename)
{
	std::vector<GLfloat> verts;
	std::vector<GLfloat> norms;
	std::vector<GLfloat> tex_coords;
	std::vector<GLuint> indices;

	Renderer::loadObj(filename, verts, norms, tex_coords, indices);
	indexCount = indices.size();
	meshID = Renderer::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), indexCount, indices.data());
	meshIndex = meshID;

	return meshID;
}

//GLuint Mesh::createMesh(unsigned num_verts, GLfloat *verts, std::vector<GLfloat> norms, std::vector<GLfloat> tex_coords, std::vector<GLuint> indices)
//{
//	indexCount = indices.size();
//	meshIndex = Renderer::createMesh(num_verts, verts, nullptr, norms.data(), tex_coords.data(), indexCount, indices.data());
//
//	return meshIndex;
//}

////Function takes in the model matrix and vec3 position.
glm::mat4 Mesh::meshTranslation(glm::mat4 modelMatrix, glm::vec3 position)
{
	return glm::translate(modelMatrix, position);
}

////Function takes in model matrix and a vec3 scaler.
////anything above the value 1 will be increase in size of the model in the axis appropriate.
////Anything below the value 1 will decrease the size of the model in the axis appropriate.
////Pass in any value that is higher than zero.
glm::mat4 Mesh::meshScaling(glm::mat4 modelMatrix, glm::vec3 scale)
{
	return glm::scale(modelMatrix, scale);
}

////Function takes the model matrix and a rotation in degrees and a vec3 rotate for the axis to rotate around.
////Anything higher than or less than 0 in the vec3 parameter will result in that axis being rotated.
////if value is 0 there will be no rotation in that axis.
glm::mat4 Mesh::meshRotation(glm::mat4 modelMatrix, GLfloat rotation, glm::vec3 rotate)
{
	return glm::rotate(modelMatrix, float(rotation * DEG_TO_RADIAN), rotate);
}

void Mesh::drawMesh(GLuint meshID)
{
	Renderer::drawObj(meshID, indexCount, GL_TRIANGLES);
}

void Mesh::drawFBXMesh(GLuint shader)
{
	//Renderer::drawFBXMesh(shader);

	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
										  // retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = Textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++); // transfer unsigned int to stream
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = std::to_string(heightNr++); // transfer unsigned int to stream

												 // now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader, (name + number).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, Textures[i].id);
	}

	// draw mesh
	glBindVertexArray(shader);
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}