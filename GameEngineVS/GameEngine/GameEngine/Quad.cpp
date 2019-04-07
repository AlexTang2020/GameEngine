#include "Quad.h"


Quad::Quad(GLuint VAO)
{
	vertices[0] = Vertex3D(0.5f, 0.5f, 0.f, 1.0f, 1.0f);
	vertices[1] = Vertex3D(0.5f, -0.5f, 0.f, 1.0f, 0.0f);
	vertices[2] = Vertex3D(-0.5f, -0.5f, 0.f, 0.0f, 0.0f);
	vertices[3] = Vertex3D(-0.5f, 0.5f, 0.f, 0.0f, 1.0f);


	indices[0] = (unsigned int)0;		
	indices[1] = (unsigned int)1;		
	indices[2] = (unsigned int)3;		

	indices[3] = (unsigned int)1;		
	indices[4] = (unsigned int)2;		
	indices[5] = (unsigned int)3;		

	loadQuad(VAO, VBO, EBO);
}

Quad::~Quad()
{
}

void Quad::loadQuad(GLuint VAO, GLuint VBO, GLuint EBO)
{
	//Initialized buffers
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

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

void Quad::deleteQuad(GLuint VAO, int va)
{
	glDeleteVertexArrays(va, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
