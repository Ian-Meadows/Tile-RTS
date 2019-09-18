#include "Time.h"
#include <GLFW/glfw3.h>
#include <iostream>



namespace Time {
	namespace {
		double deltaTime;
		int currentFPS;
		int FPS;

		double currentFrame;
		double lastFrame;

		double currentTime = 0;

		bool debug;
	}

	double Time::GetFPS() {
		return FPS;
	}

	double Time::GetDeltaTime() {
		return deltaTime;
	}

	void Time::Init(bool debug) {
		deltaTime = 0;
		FPS = 0;
		currentFrame = glfwGetTime();
		lastFrame = glfwGetTime();
		Time::debug = debug;
	}

	void Time::Update() {
		lastFrame = currentFrame;
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		
		currentTime += deltaTime;
		if (currentTime >= 1.0) {
			FPS = currentFPS;
			currentFPS = 0;
			if (debug) {
				std::cout << FPS << std::endl;
			}
			currentTime = 0;
		}
		currentFPS++;

	}
}
