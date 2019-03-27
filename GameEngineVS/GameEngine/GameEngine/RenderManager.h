#pragma once
#include "Header.h"
class RenderManager
{
public:
	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	/*
	// camera
	Camera camera = Camera( Vector3D(0.0f, 0.0f, 3.0f));
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;
	*/
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


	void display(GLFWwindow* window, Shader ourShader);
	void processInput(GLFWwindow *window);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void loadTexture();

	int run();
};

static int bufferCount = 0;
static unsigned int VBO, VAO, EBO = 0;
int GLFWwindowCheck(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);