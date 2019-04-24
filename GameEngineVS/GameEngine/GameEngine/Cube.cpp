#include "Cube.h"

void Cube::loadCube(GLuint VAO, GLuint VBO, GLuint EBO)
{
	/*
	float pvalues[numIndices * 3];
	float tvalues[numIndices * 2];
	//float nvalues[numIndices * 3];


	for (int i = 0; i < numIndices; i++)
	{
		pvalues[i * 3] = (float)(vertices[indices[i]]).location.x;
		pvalues[i * 3 + 1] = (float)(vertices[indices[i]]).location.y;
		pvalues[i * 3 + 2] = (float)(vertices[indices[i]]).location.z;
		tvalues[i * 2] = (float)(vertices[indices[i]]).s;
		tvalues[i * 2 + 1] = (float)(vertices[indices[i]]).t;
		//nvalues[i * 3] = (float)(vertices[indices[i]]).normal.x;
		//nvalues[i * 3 + 1] = (float)(vertices[indices[i]]).normal.y;
		//nvalues[i * 3 + 2] = (float)(vertices[indices[i]]).normal.z;
	}
	*/

	//Initialized buffers
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// vertex positions
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

void Cube::deleteCube(GLuint VAO, int va)
{
		glDeleteVertexArrays(va, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
}

Cube::Cube(GLuint VAO)
{
	//Front
	vertices[0] = Vertex3D(-0.5f, -0.5f, 0.5f, 0.f, 0.f);		vertices[0].setNormal(Vector3D(0.0f, 0.0f, 1.0f));
	vertices[1] = Vertex3D(-0.5f, 0.5f, 0.5f, 0.f, 1.f);		vertices[1].setNormal(Vector3D(0.0f, 0.0f, 1.0f));
	vertices[2] = Vertex3D(0.5f, -0.5f, 0.5f, 1.f, 0.f);		vertices[2].setNormal(Vector3D(0.0f, 0.0f, 1.0f));

	vertices[3] = Vertex3D(-0.5f, 0.5f, 0.5f, 0.f, 1.f);		vertices[3].setNormal(Vector3D(0.0f, 0.0f, 1.0f));
	vertices[4] = Vertex3D(0.5f, -0.5f, 0.5f, 1.f, 0.f);		vertices[4].setNormal(Vector3D(0.0f, 0.0f, 1.0f));
	vertices[5] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 1.f);			vertices[5].setNormal(Vector3D(0.0f, 0.0f, 1.0f));

	//Right
	vertices[6] = Vertex3D(0.5f, -0.5f, 0.5f, 0.f, 0.f);		vertices[6].setNormal(Vector3D(1.0f, 0.0f, 0.0f));
	vertices[7] = Vertex3D(0.5f, 0.5f, 0.5f, 0.f, 1.f);			vertices[7].setNormal(Vector3D(1.0f, 0.0f, 0.0f));
	vertices[8] = Vertex3D(0.5f, 0.5f, -0.5f, 1.f, 1.f);		vertices[8].setNormal(Vector3D(1.0f, 0.0f, 0.0f));

	vertices[9] = Vertex3D(0.5f, 0.5f, -0.5f, 1.f, 1.f);		vertices[9].setNormal(Vector3D(1.0f, 0.0f, 0.0f));
	vertices[10] = Vertex3D(0.5f, -0.5f, -0.5f, 1.f, 0.f);		vertices[10].setNormal(Vector3D(1.0f, 0.0f, 0.0f));
	vertices[11] = Vertex3D(0.5f, -0.5f, 0.5f, 0.f, 0.f);		vertices[11].setNormal(Vector3D(1.0f, 0.0f, 0.0f));

	//Back
	vertices[12] = Vertex3D(0.5f, -0.5f,-0.5f, 0.f, 0.f);		vertices[12].setNormal(Vector3D(0.0f, 0.0f, -1.0f));
	vertices[13] = Vertex3D(0.5f, 0.5f, -0.5f, 0.f, 1.f);		vertices[13].setNormal(Vector3D(0.0f, 0.0f, -1.0f));
	vertices[14] = Vertex3D(-0.5f, -0.5f, -0.5f, 1.f, 0.f);		vertices[14].setNormal(Vector3D(0.0f,0.0f,  -1.0f));

	vertices[15] = Vertex3D(-0.5f, -0.5f, -0.5f, 1.f, 0.f);		vertices[15].setNormal(Vector3D(0.0f, 0.0f, -1.0f));
	vertices[16] = Vertex3D(-0.5f, 0.5f, -0.5f, 1.f, 1.f);		vertices[16].setNormal(Vector3D(0.0f, 0.0f, -1.0f));
	vertices[17] = Vertex3D(0.5f, 0.5f, -0.5f, 0.f, 1.f);		vertices[17].setNormal(Vector3D(0.0f, 0.0f, -1.0f));

	//Left
	vertices[18] = Vertex3D(-0.5f, -0.5f, -0.5f, 0.f, 0.f);		vertices[18].setNormal(Vector3D(-1.0f, 0.0f, 0.0f));
	vertices[19] = Vertex3D(-0.5f, 0.5f, -0.5f, 0.f, 1.f);		vertices[19].setNormal(Vector3D(-1.0f, 0.0f, 0.0f));
	vertices[20] = Vertex3D(-0.5f, 0.5f, 0.5f, 1.f, 1.f);		vertices[20].setNormal(Vector3D(-1.0f, 0.0f, 0.0f));

	vertices[21] = Vertex3D(-0.5f, 0.5f, 0.5f, 1.f, 1.f);		vertices[21].setNormal(Vector3D(-1.0f, 0.0f, 0.0f));
	vertices[22] = Vertex3D(-0.5f, -0.5f, 0.5f, 1.f, 0.f);		vertices[22].setNormal(Vector3D(-1.0f, 0.0f, 0.0f));
	vertices[23] = Vertex3D(-0.5f, -0.5f, -0.5f, 0.f, 0.f);		vertices[23].setNormal(Vector3D(-1.0f, 0.0f, 0.0f));

	//Top
	vertices[24] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 0.f);		vertices[24].setNormal(Vector3D(0.0f, 1.0f, 0.0f));
	vertices[25] = Vertex3D(-0.5f, 0.5f, 0.5f, 0.f, 0.f);		vertices[25].setNormal(Vector3D(0.0f, 1.0f, 0.0f));
	vertices[26] = Vertex3D(-0.5f, 0.5f, -0.5f, 0.f, 1.f);		vertices[26].setNormal(Vector3D(0.0f, 1.0f, 0.0f));

	vertices[27] = Vertex3D(-0.5f, 0.5f, -0.5f, 0.f, 1.f);		vertices[27].setNormal(Vector3D(0.0f, 1.0f, 0.0f));
	vertices[28] = Vertex3D(0.5f, 0.5f, -0.5f, 1.f, 1.f);		vertices[28].setNormal(Vector3D(0.0f, 1.0f, 0.0f));
	vertices[29] = Vertex3D(0.5f, 0.5f, 0.5f, 1.f, 0.f);		vertices[29].setNormal(Vector3D(0.0f, 1.0f, 0.0f));

	//Bottom
	vertices[30] = Vertex3D(-0.5f, -0.5f, -0.5f, 0.f, 0.f);		vertices[30].setNormal(Vector3D(0.0f, -1.0f, 0.0f));
	vertices[31] = Vertex3D(-0.5f, -0.5f, 0.5f, 0.f, 1.f);		vertices[31].setNormal(Vector3D(0.0f, -1.0f, 0.0f));
	vertices[32] = Vertex3D(0.5f, -0.5f, -0.5f, 1.f, 0.f);		vertices[32].setNormal(Vector3D(0.0f, -1.0f, 0.0f));

	vertices[33] = Vertex3D(-0.5f, -0.5f, 0.5f, 0.f, 1.f);		vertices[33].setNormal(Vector3D(0.0f, -1.0f, 0.0f));
	vertices[34] = Vertex3D(0.5f, -0.5f, -0.5f, 1.f, 0.f);		vertices[34].setNormal(Vector3D(0.0f, -1.0f, 0.0f));
	vertices[35] = Vertex3D(0.5f, -0.5f, 0.5f, 1.f, 1.f);		vertices[35].setNormal(Vector3D(0.0f, -1.0f, 0.0f));

	for (int i = 0; i < numIndices; i++) {
		indices[i] = (unsigned int) i;
	}
	loadCube(VAO,VBO,EBO);
}

Cube::~Cube()
{

}
