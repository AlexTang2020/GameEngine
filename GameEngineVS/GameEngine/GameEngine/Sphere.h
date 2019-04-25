#pragma once
#include "shader.h"
#include "Vertex3D.h"
#include "RenderManager.h"


class Sphere
{
public:
	Sphere(GLuint VAO);
	~Sphere();

	static const int prec = 24;
	static const int numVertices = (prec + 1)*(prec + 1);
	static const int numIndices = prec * prec * 6;
	int indices[numIndices];
	Vertex3D vertices[numVertices];
	unsigned int VBO, EBO;

	void calculateVertandInd();														//Calculate Vertices and Indices for Sphere
	void loadSphere(GLuint VAO, GLuint VBO, GLuint EBO);							//Loads and binds sphere
	void deleteSphere();	//Deletes sphere from buffers

};