#pragma once
#include "Manager.h"
#include "Camera.h"
#include "Math.h"
#include "Graphics.h"
#include "Model.h"

class RenderManager
{
public:
	
	RenderManager()
	{
		std::cout << "RenderManager created\n";
	}
	~RenderManager()
	{
		std::cout << "RenderManager destroyed\n";
	}

	void GLFWSetUp();

	int loadPointers();

	//Deal with loading of vaos and vbos
	void assignBuffers(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb);


	void display(GLFWwindow* window, Shader ourShader, Shader mShader);
	void processInput(GLFWwindow *window);
	unsigned int loadTexture(char const* path);

	int run();
};

int GLFWwindowCheck(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


