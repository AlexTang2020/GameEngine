#pragma once
#include "shader.h"
#include "Vertex3D.h"

class Sphere
{
public:
	static const int prec = 48;
	int indices[prec*prec*6];		//Placeholder value
	float vertices[(prec + 1)*(prec + 1)];

	//Calculate Vertices and Indices for Sphere
	void calculateVertandInd(int indices, float vertices); //May just do in header
	void loadSphere(GLuint VAO, GLuint VBO, GLuint EBO);
	void deleteSphere(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb);
};
