#pragma once
#include "UIElement.h"
#include "Shader.h"

#include "Shape.h"
#include "TextElement.h"

enum ButtonPosition {
	Left, Right, Top, Bottom,
	TopLeft, TopRight,
	BottomLeft, BottomRight,
	Center
};

class Button :
	public UIElement
{
public:
	Button();
	Button(glm::vec2 position, glm::vec2 size, float textSize);
	Button(ButtonPosition buttonPos, glm::vec2 size, float textSize);
	~Button();

	void Draw();
	virtual void Update() final;

	void SetText(std::string text);
	std::string GetText();

	glm::vec2 size;

	//use hex
	int buttonColor;
	//use vec3
	glm::vec3 textColor;

protected:
	virtual void ButtonPressed();
	virtual void ButtonReleased();
	virtual void MouseEntered();
	virtual void MouseInside();
	virtual void MouseExited();

	
	virtual void ButtonUpdated();

private:
	Shape* shape;
	TextElement* textElement;

	glm::vec2 textPosition;

	Shader* shapeShader;
	Shader* textShader;

	void CheckButton();

	void InitButton(float textSize);

	//button helpers
	bool mouseInside = false;


};

