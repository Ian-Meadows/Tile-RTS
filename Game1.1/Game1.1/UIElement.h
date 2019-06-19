#pragma once
#include <string>

class UIElement
{
public:
	UIElement();
	~UIElement();

	void Draw();

	//name of ui element default = UI
	std::string name = "UI";
};

