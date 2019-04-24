#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Vertex3D.h"
#include "shader.h"

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	/*  Mesh Data  */
	std::vector<Vertex3D> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	unsigned int VAO;

	/*  Functions  */
	// constructor
	Mesh(std::vector<Vertex3D> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	

	// render the mesh
	void Draw(Shader shader);

private:
	/*  Render data  */
	unsigned int VBO, EBO;

	/*  Functions    */
	// initializes all the buffer objects/arrays
	void setupMesh();
};