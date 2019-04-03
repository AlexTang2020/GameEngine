#pragma once
#include "shader.h"
#include "Vertex3D.h"
#include "RenderManager.h"


class Quad
{
public:
	Quad();
	~Quad();

	static const int numVertices = 4;
	static const int numIndices = 6;
	unsigned int indices[numIndices];
	Vertex3D vertices[numVertices];

	void loadQuad(GLuint VAO, GLuint VBO, GLuint EBO);								//Loads and binds quad
	void deleteQuad(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb);	//Deletes quad from buffers

private:

};