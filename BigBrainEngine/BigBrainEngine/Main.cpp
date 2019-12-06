#include "window.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

// Default screen res 
#define xRES 1000
#define yRES 1000

// Functions
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Camera
Camera camera(glm::vec3(2.0f, 0.0f, 3.0f));
float lastX = xRES / 2.0f;
float lastY = yRES / 2.0f;
bool firstMouse = true;

glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;

int windowWidth, windowHeight;

// lighting
glm::vec3 lightPos(0.0f, 1.0f, 1.0f);

int main(int argc)
{
	// Cjeck for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	 
	// Creating a window
	if (!Window_intit(xRES, yRES, (char*)"Big Brain"))
	{
		std::cout << "Failed to load window" << std::endl;
		return 1;
	}

	// Allow openGL to resize contents of window
	glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
	glfwSetCursorPosCallback(Window, mouse_callback);
	glfwSetScrollCallback(Window, scroll_callback);

	windowWidth = xRES;
	windowHeight = yRES;

	// Initializing Glew
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew is not havig a good time" << std::endl;
	}

	// Outputting OpenGL Version and build
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	// Get Shader
	Shader shader("LightingShader.shader");
	Shader lampShader("LightSource.shader");
	Shapes3D* shapes3D = new Shapes3D();

	// first, configure the cube's VAO (and VBO)
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shapes3D->Cube), shapes3D->Cube, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Need to add UVS back


	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	float rotation = 0.0f;
	// If the window is not closed enable the engine loop
	while (!Window_shouldClose())
	{
		processInput(Window);
		Update_Window();

		// be sure to activate shader when setting uniforms/drawing objects
		shader.use();
		shader.setVec3("light.position", lightPos);
		shader.setVec3("viewPos", camera.Position);

		// light properties
		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
		shader.setVec3("light.ambient", ambientColor);
		shader.setVec3("light.diffuse", diffuseColor);
		shader.setVec3("light.specular", glm::vec3( 1.0f, 1.0f, 1.0f));

		// material properties
		shader.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		shader.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
		shader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f)); // specular lighting doesn't have full effect on this object's material
		shader.setFloat("material.shininess", 32.0f);

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		// world transformation (Cube)
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0));
		shader.setMat4("model", model);

		// render the cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		


		// Lamp object
		lampShader.use();
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lampShader.setMat4("model", model);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	delete shapes3D;
	// Destroy the window and free memory
	Window_destroy();

	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, delta);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, delta);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, delta);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, delta);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glfwGetWindowSize(window, &width, &height);
	windowWidth = width;
	windowHeight = height;
	projection = glm::perspective((float)glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos;

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}