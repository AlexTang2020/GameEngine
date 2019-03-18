#pragma once
#include "shader.h"

class Quad
{
public:
	Quad();
	~Quad();

	int vertices;
	int indicees;

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