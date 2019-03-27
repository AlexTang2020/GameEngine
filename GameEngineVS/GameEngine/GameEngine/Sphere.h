#pragma once
#include "shader.h"
#include "Vertex3D.h"
#include "RenderManager.h"


class Sphere
{
public:
	Sphere();
	~Sphere();

	static const int prec = 48;
	static const int numVertices = (prec + 1)*(prec + 1);
	static const int numIndices = prec * prec * 6;
	int indices[numIndices];
	Vertex3D vertices[numVertices];

	//Calculate Vertices and Indices for Sphere
	void calculateVertandInd();
	void loadSphere(GLuint VAO, GLuint VBO, GLuint EBO);
	void deleteSphere(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb);

};