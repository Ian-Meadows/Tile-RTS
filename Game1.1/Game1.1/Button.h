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
	virtual void Update() final;

	glm::vec2 size;

protected:
	virtual void ButtonPressed();
	virtual void ButtonReleased();
	virtual void MousedEntered();
	virtual void MouseExited();

	
	virtual void ButtonUpdated();

private:
	Shape* shape;
	TextElement* text;

	glm::vec2 textPosition;

	Shader* shapeShader;
	Shader* textShader;

	void CheckButton();
};

