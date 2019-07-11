#include "UIHandler.h"
#include "SceneHandler.h"
#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>

#define PERSPECTIVE_SCALE 5.0f

namespace UIHandler {
	namespace {
		//TODO::Create UI shaders(needs to handle text)
		Shader* textShader;
		Shader* shapeShader;

		Scene* currentScene = nullptr;

		glm::mat4 view = glm::mat4(1.0f);;
		glm::mat4 projection;

		glm::ivec2 resolution;
	}

	void Init() {
		//create shaders
		textShader = nullptr;
		shapeShader = new Shader("ShapeVertexShader.vert", "ShapeFragmentShader.frag");

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));

		//TODO: actually setup for dynamic resolutions
		resolution = glm::ivec2(XRESOLUTION, YRESOLUTION);

		projection = glm::ortho(-(resolution.x / PERSPECTIVE_SCALE), resolution.x / PERSPECTIVE_SCALE,
			-(resolution.y / PERSPECTIVE_SCALE), resolution.y / PERSPECTIVE_SCALE,
			0.1f, 10.0f);
	}
	void Draw() {
		if (currentScene == nullptr) {
			currentScene = SceneHandler::GetCurrentScene();
		}
		else if (!currentScene->isActive) {
			currentScene = SceneHandler::GetCurrentScene();
		}

		shapeShader->use();
		shapeShader->setMat4("view", view);
		shapeShader->setMat4("projection", projection);
		

		//get ui in current scene
		std::vector<UIElement*>* ui = currentScene->GetUIElements();
		for (int i = 0; i < (*ui).size(); ++i) {
			(*ui)[i]->Draw();
		}

	}
	void Uninit() {
		delete shapeShader;
	}


	Shader* UIHandler::GetTextShader() {
		return textShader;
	}
	Shader* UIHandler::GetShapeShader() {
		return shapeShader;
	}



	glm::vec2 UIHandler::GetUpperLeft() {
		return glm::vec2(-(resolution.x / PERSPECTIVE_SCALE), resolution.y / PERSPECTIVE_SCALE);
	}
	glm::vec2 UIHandler::GetUpperRight() {
		return glm::vec2(resolution.x / PERSPECTIVE_SCALE, resolution.y / PERSPECTIVE_SCALE);
	}
	glm::vec2 UIHandler::GetLowerLeft() {
		return glm::vec2(-(resolution.x / PERSPECTIVE_SCALE), -(resolution.y / PERSPECTIVE_SCALE));
	}
	glm::vec2 UIHandler::GetLowerRight() {
		return glm::vec2(resolution.x / PERSPECTIVE_SCALE, -(resolution.y / PERSPECTIVE_SCALE));
	}
}
