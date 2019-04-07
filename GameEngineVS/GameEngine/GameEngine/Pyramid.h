#pragma once
#include "shader.h"
#include "Vertex3D.h"
#include "RenderManager.h"


class Pyramid
{
public:
	static const int numVertices = 11;
	static const int numIndices = 18;
	unsigned int indices[numIndices];
	Vertex3D vertices[numVertices];
	unsigned int VBO, EBO;

	Pyramid(GLuint VAO);
	~Pyramid();

	void loadPyramid(GLuint VAO, GLuint VBO, GLuint EBO);								//Loads and binds pyramid
	void deletePyramid(GLuint VAO, int va);		//Deletes pyramid from buffers
private:

};
