#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES


#include "RenderManager.h"
//using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera = Camera(Vector3D(0.0f, 0.0f, 3.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector3D(0.0f, 0.0f, -1.0f), YAW, PITCH);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

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

void RenderManager::display(GLFWwindow* window, Shader ourShader, GLuint VAO) {
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
		/*
		Matrix4 transform = Matrix4();
		transform.setIdentity();
		Vector3D trans = Vector3D(0.5f, -.5f, 0.0f);
		Vector3D rAxis = Vector3D(0.0f, 0.0f, 1.0f);
		//transform = translate(trans.x, trans.y, trans.z);
		//transform = rotateAtMat((float)glfwGetTime(), transform, rAxis);
		transform = rotateAtCenter((float) glfwGetTime(), trans, rAxis);
		*/

		// be sure to activate shader when setting uniforms/drawing objects
		ourShader.use();
		/*
		glUniform3f(glGetUniformLocation(ourShader.ID, "light.position"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(ourShader.ID, "viewPos"), 0.0f, 0.0f, 0.0f);

		// light properties
		glUniform3f(glGetUniformLocation(ourShader.ID, "light.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(ourShader.ID, "light.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(ourShader.ID, "light.specular"), 0.0f, 0.0f, 0.0f);

		// material properties
		ourShader.setFloat("material.shininess", 64.0f);
		*/
		
		//Basic set up to test when transformation is resolved
		Matrix4 model = Matrix4();
		Matrix4 view = Matrix4();
		Matrix4 projection = Matrix4(); 

		model.setIdentity();
		view.setIdentity();
		projection.setIdentity();

		model = rotate(model, glfwGetTime(), 0.0f, 0.0f, 1.0f);
		model = translate(model, 0.0f, 0.0f, -2.0f);
		//model = scale(model, 0.5f,0.5f,0.5f);

		projection = perspective((float)(45.0f * M_PI) / 180.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection.mat4);

		//view = camera.lookAt(camera.Position, camera.Position+camera.Front, camera.Up);		
		view = translate(view, 0.0f, 0.0f, -1.0f);

		ourShader.setMat4("model", model.mat4);
		ourShader.setMat4("view", view.mat4);


		// pass them to the shaders (3 different ways)
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		
		//unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &model.mat4[0][0]);		//Can use value_ptr(transform) as well

		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_TRIANGLES, 13824, GL_UNSIGNED_INT, 0);

		/*
		//NEED TO FIX TRANSFORMS
		lightingShader.use();
		lightingShader.setMat4("projection", projection.mat4);
		lightingShader.setMat4("view", view.mat4);
		model = translate(0.0f,0.0f,0.0f);
		model = scale(0.2f,0.2f,0.2f); // a smaller cube
		lightingShader.setMat4("model", model.mat4);
		glBindVertexArray(lightVAO);
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

	//Cant place all class primitives in a single array
	//Must make an array for each primitive (Instancing)
	//Can be fixed if all objects were under a messh class instead using ASSIMP

	unsigned int VAO;			//LearnOpengl.com Instancing Tutorial for reorganizing primitives
    glGenVertexArrays(1, &VAO);	//Place VAO and VAO gen inside primitive class, just make array of class object and set up VAO binding

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	// build and compile our shader program
	// ------------------------------------
	//Shader lightingShader("lightVert.shader", "lightFrag.shader");
	Shader ourShader("vert.shader", "frag.shader");

	//Cube cube(VAO);
	//Quad quad(VAO);
	Pyramid pyr(VAO);
	//Sphere sph(VAO);

	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// shader configuration
	// --------------------
	ourShader.use();
	//ourShader.setInt("material.diffuse", 0);
	//ourShader.setInt("material.specular", 1);

	unsigned int diffuseMap = loadTexture("animefood.png");
	
	display(window, ourShader, VAO);
	
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	//cube.deleteCube(VAO, 1);
	//glDeleteVertexArrays(1, &lightVAO);
	//quad.deleteQuad(VAO, 1);
	pyr.deletePyramid(VAO,1);
	//sph.deleteSphere(VAO,1);

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
