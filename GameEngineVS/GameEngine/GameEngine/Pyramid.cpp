#include "Pyramid.h"

Pyramid::Pyramid()
{
	vertices[0] = Vertex3D(0.f, 0.5f, 0.f, .5f, 1.f);
	vertices[1] = Vertex3D(-1.f, -0.5f, 1.f, 0.f, 0.f);
	vertices[2] = Vertex3D(1.f, -0.5f, 1.f, 1.f, 0.f);
	vertices[3] = Vertex3D(1.f, -0.5f, 1.f, 0.f, 0.f);
	vertices[4] = Vertex3D(1.f, -0.5f, -1.f, 1.f, 0.f);
	vertices[5] = Vertex3D(1.f, -0.5f, -1.f, 0.f, 0.f);
	vertices[6] = Vertex3D(-1.f, -0.5f, -1.f, 1.f, 0.f);
	vertices[7] = Vertex3D(-1.f, -0.5f, -1.f, 0.f, 0.f);
	vertices[8] = Vertex3D(-1.f, -0.5f, 1.f, 1.f, 0.f);
	vertices[9] = Vertex3D(-1.f, -0.5f, -1.f, 0.f, 1.f);
	vertices[10] = Vertex3D(1.f, -0.5f, -1.f, 1.f, 1.f);

	indices[0] = 0;		indices[1] = 1;		indices[2] = 2;		//Front Triangle
	indices[3] = 0;		indices[4] = 3;		indices[5] = 4;		//Right Triangle
	indices[6] = 0;		indices[7] = 5;		indices[8] = 6;		//Back Triangle
	indices[9] = 0;		indices[10] = 7;	indices[11] = 8;	//Left Triangle
	indices[12] = 9;	indices[13] = 1;	indices[14] = 2;	//Bottom Front Left Triangle
	indices[15] = 9;	indices[16] = 10;	indices[17] = 2;	//Bottom Back Right Triangle
}

Pyramid::~Pyramid()
{
}

void Pyramid::loadPyramid(GLuint VAO, GLuint VBO, GLuint EBO)
{
	
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)0);

	// vertex texture coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, s));
	// vertex normals
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, normal));

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	
}

void Pyramid::deletePyramid(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb)
{
	glDeleteVertexArrays(va, &VAO);
	glDeleteBuffers(vb, &VBO);
	glDeleteBuffers(eb, &EBO);
}
