#pragma once
#include "shader.h"
#include "Vertex3D.h"

class Quad
{
public:
	Quad();
	~Quad();

	Vertex3D vertices[5];
	int indices[4] = {0, 1, 2, 3};

	void loadQuad(GLuint VAO, GLuint VBO, GLuint EBO);
	void deleteQuad(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb);

private:

};

Quad::Quad()
{
}

Quad::~Quad()
{
}