#pragma once
#include "shader.h"
#include "Vertex3D.h"

class Pyramid
{
public:
	static const int numVertices = 5;
	static const int numIndices = 15;
	int indices[numIndices];
	Vertex3D vertices[numVertices];

	Pyramid();
	~Pyramid();

	void loadPyramid(GLuint VAO, GLuint VBO, GLuint EBO);
	void deletePyramid(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb);
private:

};
