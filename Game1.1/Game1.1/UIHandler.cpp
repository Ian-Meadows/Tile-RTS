#include "UIHandler.h"
#include "SceneHandler.h"
#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>



namespace UIHandler {
	namespace {
		//TODO::Create UI shader(needs to handle text)
		Shader* textShader;
		Shader* shapeShader;

		Scene* currentScene = nullptr;
	}

	void Init() {
		//create shaders
		textShader = nullptr;
		shapeShader = new Shader("ShapeVertexShader.vert", "ShapeFragmentShader.frag");
	}
	void Draw() {
		if (currentScene == nullptr) {
			currentScene = SceneHandler::GetCurrentScene();
		}
		else if (!currentScene->isActive) {
			currentScene = SceneHandler::GetCurrentScene();
		}

		shapeShader->use();

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
		shapeShader->setMat4("view", view);

		shapeShader->setMat4("projection", Window::GetPerspective());
		

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
}
