#pragma once
#include "UIElement.h"
#include "Shader.h"

#include "Shape.h"
#include "Text.h"

class Button :
	public UIElement
{
public:
	Button();
	~Button();

	void Draw();

	glm::vec2 size;

private:
	Shape* shape;
	Text* text;

	Shader* shapeShader;
};

