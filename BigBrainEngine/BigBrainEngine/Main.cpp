#define STB_IMAGE_IMPLEMENTATION

#include "window.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "GraphicsManager.h"
#include "GameObjectManager.h"
#include <random>
#include <time.h>

// Default screen res 
#define xRES 1000
#define yRES 1000

// Functions
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void CreateHexagon(Model* model, Material* mat);
void CreateCell(int Q, int R);
glm::vec2 AxialFlatToWorld(int q, int r);
void GetFPS();

// Camera
Camera camera(glm::vec3(0.0f, 2.0f, 6.0f));
float lastX = xRES / 2.0f;
float lastY = yRES / 2.0f;
bool firstMouse = true;

//FPS stuff
double previousTime;
int frameCount = 0;

// MPV
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;

// WindowSize
int windowWidth, windowHeight;

GraphicsManager graphicManager;
GameObjectManager gameObjectManager(graphicManager);

// Grid Stuff
std::vector<GameObject*> map;
int GridSize = 10;
float HexScale = .29f;
int NumberOfSubTexturesAcross = 32;
float randomNoiseNum = 0.0f;


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

	// FPS setup
	previousTime = glfwGetTime();
	frameCount = 0;

	srand(time(NULL));
	randomNoiseNum = rand() % 999999;

	Shader lightingShader("BasicLighting_vert.shader", "BasicLighting_frag.shader");
	Shader lightShader("LightSource_vert.shader", "LightSource_frag.shader");
	graphicManager.AddShader(lightingShader);
	graphicManager.AddShader(lightShader);

	Texture texture("ImageTestTwo.bmp");
	Texture texture2("UvAtlas.png");

	Material planeMat(&lightingShader, &texture2);
	Material lightMat(&lightShader, &texture);
	graphicManager.AddMaterial(planeMat);
	graphicManager.AddMaterial(lightMat);

	Model hexModel("C:/Users/alexm/Desktop/SmallBrainEngine.git/trunk/BigBrainEngine/BigBrainEngine/Models/Hex.fbx");
	Model plane("C:/Users/alexm/Desktop/SmallBrainEngine.git/trunk/BigBrainEngine/BigBrainEngine/Models/Plane.obj");
	graphicManager.AddModel(hexModel);
	graphicManager.AddModel(plane);

	CreateHexagon(&hexModel, &planeMat);
	
	while (!Window_shouldClose())
	{
		GetFPS();

		processInput(Window);
		Update_Window();

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

		//plane
		lightingShader.use();
		lightingShader.setVec3("viewPos", camera.Position);
		lightingShader.setFloat("material.shininess", 3.0f);

		// directional light
		lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		lightingShader.setVec3("dirLight.ambient", 0.5f, 0.5f, 0.5f);
		lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

		gameObjectManager.Draw(projection, view);
	}

	for (int i = 0; i < map.size(); i++)
	{
		delete map[i];
	}

	map.clear();

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

void CreateHexagon(Model* model, Material* mat)
{
	for (int q = -GridSize; q <= GridSize; q++)
	{
		int r1 = glm::max(-GridSize, -q - GridSize);
		int r2 = glm::min(GridSize, -q + GridSize);

		for (int r = r1; r <= r2; r++)
		{
			map.push_back(new GameObject(*model, *mat));
			CreateCell(q, r);
		}
	}
}

void CreateCell(int Q, int R)
{
	glm::vec2 NewUVPos(1.0f,1.0f);

	float posQ = AxialFlatToWorld(Q, R).y;
	float posR = AxialFlatToWorld(Q, R).x;
	float noise = glm::clamp(((glm::perlin(glm::vec2(posQ / 5.0f + randomNoiseNum, posR / 5.0f + randomNoiseNum)) + 1.0f) / 2.0f),0.0f,0.9f);

	map.back()->SetPostition(glm::vec3(posQ, 0.0f, posR));
	map.back()->SetScale(glm::vec3(0.005f, noise / 20.0f, 0.005f));


	float horizontalOffset = glm::round(((noise - 1) * -1) * 16.0f);

	float verticalOffset = 0.0f;
	if (noise < 0.35f)
	{
		map.back()->SetScale(glm::vec3(0.005f, 0.015f, 0.005f));
		verticalOffset = 8.0;
	}
	else if (noise < 0.45f)
	{
		verticalOffset = 7.0;
	}
	else if (noise < 0.75f)
	{
		verticalOffset = 5.0;
	}
	else
	{
		verticalOffset = 4.0;
	}

	NewUVPos /= NumberOfSubTexturesAcross;
	NewUVPos += glm::vec2(horizontalOffset / NumberOfSubTexturesAcross, verticalOffset / NumberOfSubTexturesAcross);

	map.back()->UvPos = NewUVPos;

	gameObjectManager.AddObject(*map.back());
}

glm::vec2 AxialFlatToWorld(int q, int r)
{
	float x = HexScale * (3.0f / 2.0f * q);
	float y = HexScale * (glm::sqrt(3.0f) / 2.0f * q + (glm::sqrt(3.0f) * r));

	return glm::vec2(x, y);
}

void GetFPS()
{
	double currentTime = glfwGetTime();
	frameCount++;
	// If a second has passed.
	if (currentTime - previousTime >= 1.0)
	{
		// Display the frame count here any way you want.
		std::cout << frameCount << std::endl;

		frameCount = 0;
		previousTime = currentTime;
	}
}
