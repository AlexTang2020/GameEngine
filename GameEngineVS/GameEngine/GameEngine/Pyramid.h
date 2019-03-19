#pragma once
#include "shader.h"
#include "Vertex3D.h"

class Pyramid
{
public:
	Pyramid();
	~Pyramid();

	int vertices[15] = { 0.5f, 0.0f, 0.5f,
						-0.5f, 0.0f, 0.5f, 
						-0.5f, 0.0f, -0.5f, 
						0.5f, 0.0f, -0.5f, 
						0.0f, 0.5f, 0.0f };
	int indicees[5] = {0, 1, 2, 3, 4};

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
