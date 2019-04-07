#pragma once
#include "shader.h"
#include "Vertex3D.h"
#include "RenderManager.h"


class Quad
{
public:
	Quad(GLuint VAO);
	~Quad();

	static const int numVertices = 4;
	static const int numIndices = 6;
	unsigned int indices[numIndices];
	Vertex3D vertices[numVertices];
	unsigned int VBO, EBO;

	void loadQuad(GLuint VAO, GLuint VBO, GLuint EBO);								//Loads and binds quad
	void deleteQuad(GLuint VAO, int va);	//Deletes quad from buffers

private:

};