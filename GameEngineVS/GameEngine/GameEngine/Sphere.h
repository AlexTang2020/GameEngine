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

	void calculateVertandInd();														//Calculate Vertices and Indices for Sphere
	void loadSphere(GLuint VAO, GLuint VBO, GLuint EBO);							//Loads and binds sphere
	void deleteSphere(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb);	//Deletes sphere from buffers

};