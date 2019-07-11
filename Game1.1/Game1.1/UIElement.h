#pragma once
#include <string>
#include <glm/glm.hpp>

class UIElement
{
public:
	UIElement();
	~UIElement();

	virtual void Draw();

	//name of ui element default = UI
	std::string name = "UI";

	glm::vec2 position;
};

