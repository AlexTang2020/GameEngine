#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES


#include "RenderManager.h"

//using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera = Camera(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 1.0f, 0.0f), YAW, PITCH);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//Primitives
std::vector<Cube> cubes;				unsigned int cubeVAO;	
std::vector<Quad> quads;				unsigned int quadVAO;
std::vector<Pyramid> pyramids;			unsigned int pyrVAO;
std::vector<Sphere> spheres;			unsigned int sphVAO;
//std::vector<Cube> lights;
//std::vector<Model> models;			


void RenderManager::GLFWSetUp() {
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
}

int GLFWwindowCheck(GLFWwindow* window) {
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	return 0;
}

void RenderManager::display(GLFWwindow* window, Shader ourShader, Shader mShader) {
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	unsigned int diffuseMap = loadTexture("textures/Rainbow.png");
	unsigned int foodMap = loadTexture("textures/animefood.png");
	unsigned int maillerMap = loadTexture("textures/mailler.png");
	unsigned int papaMap = loadTexture("textures/papaBless.png");


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

		// be sure to activate shader when setting uniforms/drawing objects
		ourShader.use();
		
		
		glUniform3f(glGetUniformLocation(ourShader.ID, "light.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(ourShader.ID, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		// light properties
		glUniform3f(glGetUniformLocation(ourShader.ID, "light.ambient"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(ourShader.ID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(ourShader.ID, "light.specular"), 1.0f, 1.0f, 1.0f);

		// material properties
		ourShader.setFloat("material.shininess", 32.0f);
		
		
		//Basic set up to test when transformation is resolved
		Matrix4 model = Matrix4();
		Matrix4 view = Matrix4();
		Matrix4 projection = Matrix4(); 

		model.setIdentity();
		view.setIdentity();
		projection.setIdentity();

		//model = translate(model, 0.0f, 0.0f, 3.0f);

		projection = perspective((float)(45.0f * M_PI) / 180.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection.mat4);

		view = camera.GetViewMatrix();
		ourShader.setMat4("view", view.mat4);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, papaMap);
		model = scale(model, 100.0f, 100.0f, 100.0f);
		ourShader.setMat4("model", model.mat4);
		glBindVertexArray(cubeVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_TRIANGLES, cubes.at(0).numIndices, GL_UNSIGNED_INT, 0);


		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glBindVertexArray(cubeVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		for (int i = 0; i < 3; i++) {
			model.setIdentity();
			model = translate(model, 1.0f + 5.0f * i, 0.0f + 2.0f * i, 2.0f + 1.0f * i);
			ourShader.setMat4("model", model.mat4);
			glDrawElements(GL_TRIANGLES, cubes.at(i).numIndices, GL_UNSIGNED_INT, 0);
		}

		glBindTexture(GL_TEXTURE_2D, foodMap);
		glBindVertexArray(quadVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		for (int i = 0; i < 3; i++) {
			model.setIdentity();
			if (i == 2) {
				model = scale(model, 10.0f,10.0f,10.0f);
				model = rotate(model, M_PI/2, 1.0f, 0.0f, 0.0f);
				model = translate(model, 0.0f, -1.0f, 4.0f);
			}
			else {
				model = rotate(model, glfwGetTime(), 1.0f, 0.0f, 0.0f);
				model = translate(model, 1.0f - 2.0f * i, 0.3f + 0.5f * i, 1.0f + 2.0f * i);
			}
			ourShader.setMat4("model", model.mat4);
			glDrawElements(GL_TRIANGLES, quads.at(i).numIndices, GL_UNSIGNED_INT, 0);
		}

		glBindTexture(GL_TEXTURE_2D, papaMap);
		glBindVertexArray(pyrVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		for (int i = 0; i < 3; i++) {
			model.setIdentity();
			model = translate(model, -3.0f + 6.0f * i, -0.4f + 1.2f * i, 2.0f + 1.0f * i);
			ourShader.setMat4("model", model.mat4);
			glDrawElements(GL_TRIANGLES, pyramids.at(i).numIndices, GL_UNSIGNED_INT, 0);
		}

		glBindTexture(GL_TEXTURE_2D, maillerMap);
		glBindVertexArray(sphVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		for (int i = 0; i < 3; i++) {
			model.setIdentity();
			model = rotate(model, glfwGetTime(), 0.0f, 1.0f, 0.0f);
			model = translate(model, -2.0f + 3.0f * i, 5.0f - 2.0f * i, 4.0f + 0.5f * i);
			ourShader.setMat4("model", model.mat4);
			glDrawElements(GL_TRIANGLES, spheres.at(i).numIndices, GL_UNSIGNED_INT, 0);
		}

		/*
		mShader.use();
		model.setIdentity();
		model = translate(model, 0.0f, 0.0f, 4.0f);
		mShader.setMat4("model", model.mat4);
		//models.at(0).Draw(mShader);
		*/
		//glDrawElements(GL_TRIANGLES, 13824, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

		/*
		lShader.use();
		lShader.setMat4("projection", projection.mat4);
		lShader.setMat4("view", view.mat4);
		model.setIdentity();
		model = translate(model, 2.0f,4.0f,3.0f);
		model = scale(model, 0.2f,0.2f,0.2f); // a smaller cube
		lShader.setMat4("model", model.mat4);
		glBindVertexArray(lVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		*/

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int RenderManager::run()
{
	
	GLFWSetUp();

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game Engine", NULL, NULL);
	if (GLFWwindowCheck(window) == -1) {
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (loadPointers() == -1) {
		return -1;
	}
	
	glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &cubeVAO);	
	glGenVertexArrays(1, &quadVAO);
	glGenVertexArrays(1, &pyrVAO);
	glGenVertexArrays(1, &sphVAO);


	for (int i = 0; i < 3; i++) {
		cubes.push_back(Cube(cubeVAO));
		quads.push_back(Quad(quadVAO));
		pyramids.push_back(Pyramid(pyrVAO));
		spheres.push_back(Sphere(sphVAO));
	}

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("vert.shader", "frag.shader");
	//Shader lightingShader("lightVert.shader", "lightFrag.shader");
	Shader modShader("modelVert.shader", "modelFrag.shader");
	//Model model("sword.obj");
	//models.push_back(model);

	// shader configuration
	// --------------------
	ourShader.use();
	ourShader.setInt("material.diffuse", 0);
	ourShader.setInt("material.specular", 1);	


	display(window, ourShader, modShader);
	
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteVertexArrays(1, &pyrVAO);
	glDeleteVertexArrays(1, &sphVAO);


	for (int i = 0; i < 3; i++) {
		cubes.at(i).deleteCube();
		quads.at(i).deleteQuad();
		pyramids.at(i).deletePyramid();
		spheres.at(i).deleteSphere();
	}

	cubes.empty();
	quads.empty();
	pyramids.empty();
	spheres.empty();
	//models.empty();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void RenderManager::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(0, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(1, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(2, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(3, deltaTime);

}

unsigned int RenderManager::loadTexture(char const* path)
{

	// load and create a texture 
	// -------------------------
	unsigned int textureID;
	glGenTextures(1, &textureID);
	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 4)
			format = GL_RGBA;
		else						//nrComponents == 3
			format = GL_RGB;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
	//Credit for image handling goes to https://github.com/nothings/stb/blob/master/stb_image.h

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

int RenderManager::loadPointers() {
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	return 0;
}

//Deal with loading of vaos and vbos
void RenderManager::assignBuffers(GLuint VAO, GLuint VBO, GLuint EBO, int va, int vb, int eb) {
	glGenVertexArrays(va, &VAO);
	glGenBuffers(vb, &VBO);
	glGenBuffers(eb, &EBO);
}
