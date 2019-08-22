/*
TODOs before release
-read freetypes licence and do what is says
-make sure all licences are squared away


*/



#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input.h"
#include "Window.h"
#include "Camera.h"
#include "Game.h"
#include "Time.h"
#include "TextureAtlasCreator.h"
#include "SceneHandler.h"
#include "UIHandler.h"

//scenes
#include "MainScene.h"
#include "TestUIScene.h"

#include "Debugger.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Window::ChangeSize(width, height);
}

void AddImagesToAtlas() {
	TextureAtlasCreator::AddImageFile("Images/GunPoint.png", "Vertical Line");
	TextureAtlasCreator::AddImageFile("Images/BaseCharacter.png", "Square");
	TextureAtlasCreator::AddImageFile("Images/eyes2.png", "2 Dots");
	TextureAtlasCreator::AddImageFile("Images/head2.png", "Circle");
	//TextureAtlasCreator::AddImageFile("Images/horseman.png");

	/*
	TextureAtlasCreator::AddImageFile("Images/GunPoint.png");
	TextureAtlasCreator::AddImageFile("Images/BaseCharacter.png");
	TextureAtlasCreator::AddImageFile("Images/eyes2.png");
	TextureAtlasCreator::AddImageFile("Images/eyes2.png");
	TextureAtlasCreator::AddImageFile("Images/horseman.png");

	TextureAtlasCreator::AddImageFile("Images/GunPoint.png");
	TextureAtlasCreator::AddImageFile("Images/BaseCharacter.png");
	TextureAtlasCreator::AddImageFile("Images/eyes2.png");
	TextureAtlasCreator::AddImageFile("Images/eyes2.png");
	TextureAtlasCreator::AddImageFile("Images/horseman.png");

	TextureAtlasCreator::AddImageFile("Images/GunPoint.png");
	TextureAtlasCreator::AddImageFile("Images/BaseCharacter.png");
	TextureAtlasCreator::AddImageFile("Images/eyes2.png");
	TextureAtlasCreator::AddImageFile("Images/eyes2.png");
	TextureAtlasCreator::AddImageFile("Images/horseman.png");

	TextureAtlasCreator::AddImageFile("Images/GunPoint.png");
	TextureAtlasCreator::AddImageFile("Images/BaseCharacter.png");
	TextureAtlasCreator::AddImageFile("Images/eyes2.png");
	TextureAtlasCreator::AddImageFile("Images/eyes2.png");
	TextureAtlasCreator::AddImageFile("Images/horseman.png");
	*/

	
	
}

void InitSceneHandler() {
	SceneHandler::Init();
	//add scenes
	SceneHandler::AddScene(new MainScene());
	SceneHandler::AddScene(new TestUIScene());

	//set current scene
	//SceneHandler::SetCurrentScene("UITest");
	SceneHandler::SetCurrentScene("Game");
}

int main() {
	
	//init namespaces
	Window::InitWindow(800, 600);
	Camera::Init(glm::vec3(0, 0, -1), 0.0f);
	TextureAtlasCreator::Init(100, 20);

	AddImagesToAtlas();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

	

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(Window::GetWidth(), Window::GetHeight(), "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//init input namespace
	Time::Init(true);
	Input::InitInput(window);

	//glfwSetCursorPosCallback(window, mouse_callback);
	TextureAtlasCreator::CreateAtlas();

	UIHandler::Init();
	InitSceneHandler();
	

	while (!glfwWindowShouldClose(window))
	{
		//clear window with black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//update time to get fps and delta time
		Time::Update();

		//handle input
		Input::ProcessInput();

		//update
		SceneHandler::Update();
		Camera::Update();
		Window::Update();
		UIHandler::Update();

		//draw
		SceneHandler::Draw();
		UIHandler::Draw();

		//clear keys pressed
		Input::ClearOldInputs();


		GLenum error = glGetError();

		if (error != GL_NO_ERROR) {
			std::cout << "opengl ERROR: " << error << std::endl;
		}

		//glfw stuff
		glfwSwapBuffers(window);
		glfwPollEvents();



	}
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//get ending errors
	

	glfwTerminate(); //throws 1282 error

	

	UIHandler::Uninit();

	

	SceneHandler::Uninit();
	
	

	TextureAtlasCreator::Uninit();

	/*
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << "opengl ERROR: " << error << std::endl;
	}
	std::cin.get();
	*/
	return 0;
}

