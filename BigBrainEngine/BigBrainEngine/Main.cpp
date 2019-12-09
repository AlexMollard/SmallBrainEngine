#define STB_IMAGE_IMPLEMENTATION
#include "window.h"
#include "Shader.h"
#include "CustomTexture.h"
#include "Camera.h"
#include "Model.h"

// Default screen res 
#define xRES 1000
#define yRES 1000

// Functions
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Camera
Camera camera(glm::vec3(0.0f, 2.0f, 6.0f));
float lastX = xRES / 2.0f;
float lastY = yRES / 2.0f;
bool firstMouse = true;

glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;

int windowWidth, windowHeight;

int main(int argc, char* argv[])
{
	// Check for Memory Leaks
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

	Shader modelShader("MeshShader.shader");
	Shader lightShader("LightSource.shader");

	CustomTexture texture("ImageTestTwo.bmp");
	CustomTexture texture2("ImageTestTwoB.bmp");
	Model ourModel("C:/Users/s191067/Desktop/SmallBrainEngine.git/trunk/BigBrainEngine/BigBrainEngine/Models/Hex.fbx");
	Model plane("C:/Users/s191067/Desktop/SmallBrainEngine.git/trunk/BigBrainEngine/BigBrainEngine/Models/stan/Stan Lee.obj");

	modelShader.use();
	modelShader.setInt("texture1", 0);

	lightShader.use();
	lightShader.setInt("texture1", 0);

	glm::vec3 lightPos(2.0f, 0.0f, 0.0f);
	float rotation = 0.0f;
	while (!Window_shouldClose())
	{
		processInput(Window);
		Update_Window();
		rotation += delta * 1.0f;
		lightPos = glm::vec3(glm::sin(rotation) * 2, 0.5f, glm::cos(rotation) * 2);

		modelShader.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		modelShader.setMat4("projection", projection);
		modelShader.setMat4("view", view);

		// set light uniforms
		modelShader.setVec3("viewPos", camera.Position);
		modelShader.setVec3("lightPos", lightPos);

		//plane
		glm::mat4  model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		modelShader.setMat4("model", model);
		plane.Draw(modelShader, texture);


		// Light
		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);

		// set light uniforms
		lightShader.setVec3("viewPos", camera.Position);
		lightShader.setVec3("lightPos", 100,100,100);

		// Render Light
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));
		modelShader.setMat4("model", model);
		ourModel.Draw(lightShader, texture2);
	}

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