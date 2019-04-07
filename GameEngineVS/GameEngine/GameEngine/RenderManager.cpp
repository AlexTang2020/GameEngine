#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES


#include "RenderManager.h"
using namespace std;

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


void RenderManager::display(GLFWwindow* window, Shader ourShader, GLuint VAO) {
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
		/*
		Matrix4 transform = Matrix4();
		transform.setIdentity();
		Vector3D trans = Vector3D(0.5f, -.5f, 0.0f);
		Vector3D rAxis = Vector3D(0.0f, 0.0f, 1.0f);
		//transform = translate(trans.x, trans.y, trans.z);
		//transform = rotateAtMat((float)glfwGetTime(), transform, rAxis);
		transform = rotateAtCenter((float) glfwGetTime(), trans, rAxis);
		*/
		ourShader.use();
		
		//Basic set up to test when transformation is resolved
		Matrix4 model = Matrix4();
		Matrix4 view = Matrix4();
		Matrix4 projection = Matrix4(); 

		model.setIdentity();
		view.setIdentity();
		projection.setIdentity();
		
		model = model.rotateConcat((float)glfwGetTime(), 0.5f, 1.0f, 0.0f);
		view = translate(0.0f,0.0f,-2.0f);
		projection = perspective((45.0f*M_PI)/180.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");

		// pass them to the shaders (3 different ways)
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view.mat4[0][0]);
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		ourShader.setMat4("projection", projection.mat4);

		//Apply when camera in place
		// pass projection matrix to shader (note that in this case it could change every frame)
		//glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		//ourShader.setMat4("projection", projection);

		// camera/view transformation
		//glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		//ourShader.setMat4("view", view);
		
		//Apply model transformations
		//Matrix4 model = Matrix4();
		//model.setIdentity();
		

		
		
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &model.mat4[0][0]);		//Can use value_ptr(transform) as well

		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_TRIANGLES, 13824, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void RenderManager::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	/*
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
		*/
}

void RenderManager::loadTexture()
{
	
	// load and create a texture 
	// -------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load("animeFood.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	//Credit for image handling goes to https://github.com/nothings/stb/blob/master/stb_image.h
	
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void RenderManager::mouse_callback(GLFWwindow * window, float xpos, float ypos)
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

	//camera.ProcessMouseMovement(xoffset, yoffset);
	
}

void RenderManager::scroll_callback(GLFWwindow * window, float xoffset, float yoffset)
{
	//camera.ProcessMouseScroll(yoffset);
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

	if (loadPointers() == -1) {
		return -1;
	}
	
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("vert.shader", "frag.shader"); // you can name your shader files however you like

	//Cant place all class primitives in a single array
	//Must make an array for each primitive (Instancing)
	//Can be fixed if all objects were under a messh class instead using ASSIMP

	unsigned int VAO;			//LearnOpengl.com Instancing Tutorial for reorganizing primitives
    glGenVertexArrays(1, &VAO);	//Place VAO and VAO gen inside primitive class, just make array of class object and set up VAO binding
   
	//Cube cube(VAO);
	//Quad quad(VAO);
	Pyramid pyr(VAO);
	//Sphere sph(VAO);
	loadTexture();
	
	display(window, ourShader, VAO);
	
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	//cube.deleteCube(VAO, 1);
	//quad.deleteQuad(VAO, 1);
	pyr.deletePyramid(VAO,1);
	//sph.deleteSphere(VAO,1);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}
