#define _USE_MATH_DEFINES

#include "Sphere.h"


Sphere::Sphere() {
	for (int i = 0; i < numVertices; i++) {
		vertices[i] = Vertex3D();
	}
	calculateVertandInd();
}

Sphere::~Sphere()
{
}

void Sphere::calculateVertandInd()
{
	// calculate triangle vertices
	for (int i = 0; i <= prec; i++)
	{
		for (int j = 0; j <= prec; j++)
		{
			float y = (float)cos((180.f - i * 180.f / prec) * (M_PI/180.0f));
			float x = -(float)cos((j*360.0 / prec) * (M_PI / 180.0f))*(float)abs(cos(asin(y)));
			float z = (float)sin((j*360.0f / (float)(prec))  * (M_PI / 180.0f))*(float)abs(cos(asin(y)));
			vertices[i*(prec + 1) + j].setLocation(x, y, z);
			vertices[i*(prec + 1) + j].setS((float)j / prec);
			vertices[i*(prec + 1) + j].setT((float)i / prec);
			vertices[i*(prec + 1) + j].setNormal(Vector3D(vertices[i*(prec + 1) + j].location.x, 
														  vertices[i*(prec + 1) + j].location.y,
														  vertices[i*(prec + 1) + j].location.z));
		}
	}

	// calculate triangle indices
	for (int i = 0; i < prec; i++)
	{
		for (int j = 0; j < prec; j++)
		{
			indices[6 * (i*prec + j) + 0] = i * (prec + 1) + j;
			indices[6 * (i*prec + j) + 1] = i * (prec + 1) + j + 1;
			indices[6 * (i*prec + j) + 2] = (i + 1)*(prec + 1) + j;
			indices[6 * (i*prec + j) + 3] = i * (prec + 1) + j + 1;
			indices[6 * (i*prec + j) + 4] = (i + 1)*(prec + 1) + j + 1;
			indices[6 * (i*prec + j) + 5] = (i + 1)*(prec + 1) + j;
		}
	}
}

void Sphere::loadSphere(GLuint VAO, GLuint VBO, GLuint EBO)
{
	/*	FIX SPHERE
	Vertex3D[] vertices = mySphere.getVertices();
	int[] indices = mySphere.getIndices();

	float[] pvalues = new float[indices.length * 3];
	float[] tvalues = new float[indices.length * 2];
	float[] nvalues = new float[indices.length * 3];

	for (int i = 0; i < indices.length; i++)
	{
		pvalues[i * 3] = (float)(vertices[indices[i]]).getX();
		pvalues[i * 3 + 1] = (float)(vertices[indices[i]]).getY();
		pvalues[i * 3 + 2] = (float)(vertices[indices[i]]).getZ();
		tvalues[i * 2] = (float)(vertices[indices[i]]).getS();
		tvalues[i * 2 + 1] = (float)(vertices[indices[i]]).getT();
		nvalues[i * 3] = (float)(vertices[indices[i]]).getNormalX();
		nvalues[i * 3 + 1] = (float)(vertices[indices[i]]).getNormalY();
		nvalues[i * 3 + 2] = (float)(vertices[indices[i]]).getNormalZ();
	}

	gl.glGenVertexArrays(vao.length, vao, 0);
	gl.glBindVertexArray(vao[0]);
	gl.glGenBuffers(3, vbo, 0);

	gl.glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	FloatBuffer vertBuf = Buffers.newDirectFloatBuffer(pvalues);
	gl.glBufferData(GL_ARRAY_BUFFER, vertBuf.limit() * 4, vertBuf, GL_STATIC_DRAW);

	gl.glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	FloatBuffer texBuf = Buffers.newDirectFloatBuffer(tvalues);
	gl.glBufferData(GL_ARRAY_BUFFER, texBuf.limit() * 4, texBuf, GL_STATIC_DRAW);

	gl.glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	FloatBuffer norBuf = Buffers.newDirectFloatBuffer(nvalues);
	gl.glBufferData(GL_ARRAY_BUFFER, norBuf.limit() * 4, norBuf, GL_STATIC_DRAW);
	*/

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(Vertex3D), (void*)0);

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

void Sphere::deleteSphere(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb)
{
	glDeleteVertexArrays(va, &VAO);
	glDeleteBuffers(vb, &VBO);
	glDeleteBuffers(eb, &EBO);
}
