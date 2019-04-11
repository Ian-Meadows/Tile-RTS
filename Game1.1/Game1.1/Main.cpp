#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input.h"
#include "Window.h"
#include "Camera.h"
#include "Game.h"
#include "Time.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Window::ChangeSize(width, height);
}

int main() {
	
	
	//init namespaces
	Window::InitWindow(800, 600);
	Camera::Init(glm::vec3(0, 0, -1), 0);



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
	
	//init input namespace
	Time::Init(true);
	Input::InitInput(window);

	//glfwSetCursorPosCallback(window, mouse_callback);
	
	Game::Init();

	while (!glfwWindowShouldClose(window))
	{
		//clear window with black
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//update time to get fps and delta time
		Time::Update();

		//
		Input::ProcessInput();
		Game::Update();
		Camera::Update();
		Game::Draw();

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

	

	glfwTerminate();

	Game::Uninit();

	return 0;
}

