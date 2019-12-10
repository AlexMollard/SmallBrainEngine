#define STB_IMAGE_IMPLEMENTATION

#include "window.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Model.h"
#include "GameObject.h"

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

	Texture texture("ImageTestTwo.bmp");
	Texture texture2("ImageTestTwoB.bmp");

	Model ourModel("C:/Users/alexm/Desktop/SmallBrainEngine.git/trunk/BigBrainEngine/BigBrainEngine/Models/Hex.fbx");
	Model plane("C:/Users/alexm/Desktop/SmallBrainEngine.git/trunk/BigBrainEngine/BigBrainEngine/Models/Plane.obj");

	GameObject lightObject(&ourModel, &texture, &lightShader);
	GameObject* planeObject[10];

	for (int i = 0; i < 10; i++)
	{
		planeObject[i] = new GameObject(&plane, &texture2, &modelShader);
		planeObject[i]->SetPostition(glm::vec3(i * 2, 0, 0));
	}

	lightObject.SetScale(glm::vec3(0.005f, 0.005f, 0.005f));
	glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
	float rotation = 0.0f;

	while (!Window_shouldClose())
	{
		processInput(Window);
		Update_Window();

		rotation += delta * 1.0f;
		lightPos = glm::vec3(glm::sin(rotation), 0.25f, glm::cos(rotation));

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

		//plane
		modelShader.use();
		modelShader.setVec3("viewPos", camera.Position);
		modelShader.setVec3("lightPos", lightPos);

		for (int i = 0; i < 10; i++)
		{
			planeObject[i]->Draw(&projection, &view);
		}

		// LightObject
		lightObject.SetPostition(lightPos);
		lightObject.Draw(&projection, &view);
	}

	for (int i = 0; i < 10; i++)
	{
		delete planeObject[i];
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