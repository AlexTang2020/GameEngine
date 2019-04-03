#pragma once
#include "shader.h"
#include "Vertex3D.h"
#include "RenderManager.h"


class Cube {
public:
	static const int numVertices = 36;
	static const int numIndices = 36;
	Vertex3D vertices[numVertices];
	unsigned int indices[numIndices];
	//int bufferID;

	/*
	float vertices[144] = { -0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, 0.5f, -0.5f,
			0.5f, 0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f, 0.5f,
			0.5f, -0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f,

			-0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,

			0.5f, 0.5f, 0.5f,
			0.5f, 0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,

			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, 0.5f,
			0.5f, -0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, 0.5f, -0.5f,
			0.5f, 0.5f, -0.5f,
			0.5f, 0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, -0.5f };

	//Vertices needed to make a triangle
	int indices[36] = { 0, 1, 2, 3, 4, 5, 6,
		7, 8, 9, 10, 11, 12, 13,
		14, 15, 16, 17, 18, 19, 20,
		21, 22, 23, 24, 25, 26, 27,
		28, 29, 30, 31, 32, 33, 34, 35 };
	*/
	void loadCube(GLuint VAO, GLuint VBO, GLuint EBO);									//Loads and binds cube
	void deleteCube(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb);		//Deletes cube from buffers
	Cube();
	~Cube();
};