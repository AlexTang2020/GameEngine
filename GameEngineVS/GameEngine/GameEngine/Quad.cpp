#include "Quad.h"


Quad::Quad()
{
	bufferCount++;

	vertices[0] = Vertex3D(-1.f, -0.5f, 0.f, 0.f, 0.f);
	vertices[1] = Vertex3D(-1.f, 0.5f, 0.f, 0.f, 1.f);
	vertices[2] = Vertex3D(1.f, 0.5f, 0.f, 1.f, 1.f);
	vertices[3] = Vertex3D(1.f, -0.5f, 0.f, 0.f, 1.f);

	indices[0] = 0;		indices[1] = 1;		indices[2] = 2;		//Top Left Triangle
	indices[3] = 0;		indices[4] = 2;		indices[5] = 3;		//Bottom Right Triangle
}

Quad::~Quad()
{
}

void Quad::loadQuad(GLuint VAO, GLuint VBO, GLuint EBO)
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

void Quad::deleteQuad(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb)
{
	glDeleteVertexArrays(va, &VAO);
	glDeleteBuffers(vb, &VBO);
	glDeleteBuffers(eb, &EBO);
	bufferCount--;

}
