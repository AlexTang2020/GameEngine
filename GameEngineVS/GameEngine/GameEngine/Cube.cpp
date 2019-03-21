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
	vertices[0] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 1.f);

	vertices[1] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 1.f);
	vertices[2] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 1.f);
	vertices[3] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 1.f);
	vertices[4] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 1.f);
	vertices[5] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 1.f);
	vertices[6] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 1.f);
	vertices[7] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 1.f);

	indices[0];		indices[1];		indices[2];
	indices[3];		indices[4];		indices[5];
	indices[6];		indices[7];		indices[8];
	indices[9];		indices[10];		indices[11];
	indices[12];		indices[13];		indices[14];
	indices[15];		indices[16];		indices[17];
	indices[18];		indices[19];		indices[20];
	indices[21];		indices[22];		indices[23];
	indices[24];		indices[25];		indices[26];
	indices[27];		indices[28];		indices[29];
	indices[30];		indices[31];		indices[32];
	indices[33];		indices[34];		indices[35];
}

Cube::~Cube()
{
}
