#include "Renderer.h"
#include "rt3D.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


void Renderer::renderObject(const char* object) //this method will render an specified object
{
	//loads in the object specified with all it's data
	rt3d::loadObj(object, verts, norms, tex_coords, indices);
	mesh = rt3d::createMesh(verts.size()/3, verts.data(), nullptr, norms.data(), tex_coords.data(), size, indices.data());
}

void Renderer::renderFBX(const char* fbx) //will render the specified FBX models we use
{

}

void Renderer::draw(glm::mat4 stack, GLuint texture, glm::vec3 position, GLuint shader) //this method will draw the model specified
{
	//rt3d::updateMesh(mesh, RT3D_VERTEX, verts, size);

	glBindTexture(GL_TEXTURE_2D, texture); //asigns the objects texture
	stack = glm::translate(stack, position); //sets it's position
	stack = glm::scale(stack, glm::vec3(1 * 0.05f, 1 * 0.05, 1 * 0.05)); //sets it's size

	rt3d::setUniformMatrix4fv(shader, "modelview", glm::value_ptr(stack));
	rt3d::drawMesh(mesh, meshIndexCount, GL_TRIANGLES);
}