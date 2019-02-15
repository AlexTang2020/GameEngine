#pragma once
class RenderManager
{
public:
	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
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


	void display(GLFWwindow* window, Shader ourShader, int VAO);
	void processInput(GLFWwindow *window);
	
	int run();
};

int GLFWwindowCheck(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);