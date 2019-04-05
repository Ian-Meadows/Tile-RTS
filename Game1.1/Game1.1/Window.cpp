#include "Window.h"

namespace Window {
	//use for private methods and variables
	namespace {
		int WIDTH, HEIGHT;
	}

	//put public mathods and variables here
	void InitWindow(int width, int height) {
		WIDTH = width;
		HEIGHT = height;
	}


	//getters
	int GetWidth() {
		return WIDTH;
	}
	int GetHeight() {
		return HEIGHT;
	}

	//setters
	void SetSize(int width, int height) {
		WIDTH = width;
		HEIGHT = height;
		//TODO:actually resize window
	}
	void SetHeight(int height) {
		HEIGHT = height;
		//TODO:actually resize window
	}
	void SetWidth(int width) {
		WIDTH = width;
		//TODO:actually resize window
	}
}

