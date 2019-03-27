#pragma once
#include "shader.h"
#include "Vertex3D.h"
#include "RenderManager.h"


class Pyramid
{
public:
	static const int numVertices = 11;
	static const int numIndices = 18;
	int indices[numIndices];
	Vertex3D vertices[numVertices];

	Pyramid();
	~Pyramid();

	void loadPyramid(GLuint VAO, GLuint VBO, GLuint EBO);
	void deletePyramid(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb);
private:

};
