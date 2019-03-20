#pragma once
#include "shader.h"
#include "Vertex3D.h"

class Quad
{
public:
	Quad();
	~Quad();

	static const int numVertices = 4;
	static const int numIndices = 4;
	int indices[numIndices];
	Vertex3D vertices[numVertices];

	void loadQuad(GLuint VAO, GLuint VBO, GLuint EBO);
	void deleteQuad(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb);

private:

};