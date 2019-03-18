#pragma once
#include "shader.h"

class Pyramid
{
public:
	Pyramid();
	~Pyramid();

	int vertices;
	int indicees;

	void loadPyramid(GLuint VAO, GLuint VBO, GLuint EBO);
	void deletePyramid(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb);
private:

};

Pyramid::Pyramid()
{
}

Pyramid::~Pyramid()
{
}
