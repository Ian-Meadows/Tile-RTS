#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input.h"
#include "Window.h"
#include "TestRenderer.h"

void mouse_callback(GLFWwindow*, double, double);
void ProcessInput(GLFWwindow*);


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main() {

	
	//init namespaces
	Window::InitWindow(600, 400);




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
	Input::InitInput(window);

	//glfwSetCursorPosCallback(window, mouse_callback);
	
	TestRenderer* test = new TestRenderer();


	while (!glfwWindowShouldClose(window))
	{
		Input::ProcessInput();
		test->Update();
		test->Draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	

	glfwTerminate();

	delete test;

	return 0;
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

}

