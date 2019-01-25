#pragma once
#include "shader.h"

class Sphere
{
public:
	int indices[1];		//Placeholder value
	float vertices[1];

	//Calculate Vertices and Indices for Sphere
	void calculateVertandInd(int indices, float vertices); //May just do in header
	void loadSphere(GLuint VAO, GLuint VBO, GLuint EBO);
	void deleteSphere(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb);
};
