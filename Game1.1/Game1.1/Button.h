#pragma once
#include "UIElement.h"
#include "Shader.h"

#include "Shape.h"

class Button :
	public UIElement
{
public:
	Button();
	~Button();

	void Draw();

private:
	Shape* shape;

	Shader* shapeShader;
};

