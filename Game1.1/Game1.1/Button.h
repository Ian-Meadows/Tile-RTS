#pragma once
#include "UIElement.h"
#include "Shader.h"

#include "Shape.h"
#include "TextElement.h"

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
	TextElement* text;

	glm::vec2 textPosition;

	Shader* shapeShader;
	Shader* textShader;
};

