#include "Cube.h"


void Cube::loadCube(GLuint VAO, GLuint VBO, GLuint EBO)
{
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void Cube::deleteCube(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb)
{
		glDeleteVertexArrays(va, &VAO);
		glDeleteBuffers(vb, &VBO);
		glDeleteBuffers(eb, &EBO);
}

Cube::Cube()
{
	//Front
	vertices[0] = Vertex3D(-0.5f, -0.5f, 0.5f, 0.f, 0.f);
	vertices[1] = Vertex3D(-0.5f, 0.5f, 0.5f, 0.f, 1.f);
	vertices[2] = Vertex3D(0.5f, -0.5f, 0.5f, 1.f, 0.f);

	vertices[3] = Vertex3D(-0.5f, 0.5f, 0.5f, 0.f, 1.f);
	vertices[4] = Vertex3D(0.5f, -0.5f, 0.5f, 1.f, 0.f);
	vertices[5] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 1.f);

	//Right
	vertices[6] = Vertex3D(0.5f, -0.5f, 0.5f, 0.f, 0.f);
	vertices[7] = Vertex3D(0.5f, 0.5f, 0.5f, 0.f, 1.f);
	vertices[8] = Vertex3D(0.5f, 0.5f, -0.5f, 1.f, 1.f);

	vertices[9] = Vertex3D(0.5f, 0.5f, -0.5f, 1.f, 1.f);
	vertices[10] = Vertex3D(0.5f, -0.5f, -0.5f, 1.f, 0.f);
	vertices[11] = Vertex3D(0.5f, -0.5f, 0.5f, 0.f, 0.f);

	//Back
	vertices[12] = Vertex3D(0.5f, -0.5f,-0.5f, 0.f, 0.f);
	vertices[13] = Vertex3D(0.5f, 0.5f, -0.5f, 0.f, 1.f);
	vertices[14] = Vertex3D(-0.5f, -0.5f, -0.5f, 1.f, 0.f);

	vertices[15] = Vertex3D(-0.5f, -0.5f, -0.5f, 1.f, 0.f);
	vertices[16] = Vertex3D(-0.5f, 0.5f, -0.5f, 1.f, 1.f);
	vertices[17] = Vertex3D(0.5f, 0.5f, -0.5f, 0.f, 1.f);

	//Left
	vertices[18] = Vertex3D(-0.5f, -0.5f, -0.5f, 0.f, 0.f);
	vertices[19] = Vertex3D(-0.5f, 0.5f, -0.5f, 0.f, 1.f);
	vertices[20] = Vertex3D(-0.5f, 0.5f, 0.5f, 1.f, 1.f);

	vertices[21] = Vertex3D(-0.5f, 0.5f, 0.5f, 1.f, 1.f);
	vertices[22] = Vertex3D(-0.5f, -0.5f, 0.5f, 1.f, 0.f);
	vertices[23] = Vertex3D(-0.5f, -0.5f, -0.5f, 0.f, 0.f);

	//Top
	vertices[24] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 0.f);
	vertices[25] = Vertex3D(-0.5f, 0.5f, 0.5f, 0.f, 0.f);
	vertices[26] = Vertex3D(-0.5f, 0.5f, -0.5f, 0.f, 1.f);

	vertices[27] = Vertex3D(-0.5f, 0.5f, -0.5f, 0.f, 1.f);
	vertices[28] = Vertex3D(0.5f, 0.5f, -0.5f, 1.f, 1.f);
	vertices[29] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 0.f);

	//Bottom
	vertices[30] = Vertex3D(-0.5f, -0.5f, -0.5f, 0.f, 0.f);
	vertices[31] = Vertex3D(-0.5f, -0.5f, 0.5f, 0.f, 1.f);
	vertices[32] = Vertex3D(0.5f, -0.5f, -0.5f, 1.f, 0.f);

	vertices[33] = Vertex3D(-0.5f, -0.5f, 0.5f, 0.f, 1.f);
	vertices[34] = Vertex3D(0.5f, -0.5f, -0.5f, 1.f, 0.f);
	vertices[35] = Vertex3D(0.5f, -0.5f, 0.5f, 1.f, 1.f);

	int indices[36] = { 0, 1, 2,		3, 4, 5,		//Front
						6, 7, 8,		9, 10, 11,		//Right
						12, 13,	14,		15, 16,	17,		//Back
						18, 19, 20,		21, 22, 23,		//Left
						24, 25, 26,		27,	28, 29,		//Top
						30, 31, 32,		33, 34, 35		//Bottom
	};		
}

Cube::~Cube()
{
}
