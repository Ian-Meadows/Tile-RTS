#include "Button.h"
#include "UIHandler.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ScreenMath.h"
#include "Input.h"
#include "Window.h"
#include "Debugger.h"


Button::Button(std::string name) : UIElement()
{
	this->name = name;
	

	size = glm::vec2(50, 20);

	//this code will lock the button to the corner of the screen
	//position = glm::vec2(UIHandler::GetUpperRight().x - (size.x / 2), UIHandler::GetUpperRight().y - (size.y / 2));
	//position = ScreenMath::GetUpperRight(size);
	position = glm::vec2(0.0f, 0.0f);
	
	//textPosition = glm::vec2(size.x / 2, 0);

	InitButton(0.15f);
}

Button::Button(std::string name, glm::vec2 position, glm::vec2 size, float textSize) {
	this->name = name;

	InitButton(textSize);

	this->size = size;
	this->position = position;
}
Button::Button(std::string name, ButtonPosition buttonPos, glm::vec2 size, float textSize) {
	this->name = name;

	InitButton(textSize);

	this->size = size;
	switch (buttonPos) {
		case Left:
			position = ScreenMath::GetLeft(size);
			break;
		case Right:
			position = ScreenMath::GetRight(size);
			break;
		case Top:
			position = ScreenMath::GetTop(size);
			break;
		case Bottom:
			position = ScreenMath::GetBottom(size);
			break;
		case TopLeft:
			position = ScreenMath::GetUpperLeft(size);
			break;
		case TopRight:
			position = ScreenMath::GetUpperRight(size);
			break;
		case BottomLeft:
			position = ScreenMath::GetLowerLeft(size);
			break;
		case BottomRight:
			position = ScreenMath::GetLowerRight(size);
			break;
		case Center:
			position = glm::vec2(0.0f, 0.0f);
			break;
		default:
			position = glm::vec2(0.0f, 0.0f);

	}
}

void Button::InitButton(float textSize) {
	shapeShader = UIHandler::GetShapeShader();
	textShader = UIHandler::GetTextShader();

	float vert[] = {
			0.5f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indi[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	ShapeInput* input = new ShapeInput(vert, sizeof(vert), indi, 6);


	shapeShader->use();
	shape = new Shape(input);

	textShader->use();
	textElement = new TextElement(textSize, "New Button");

	buttonColor = 0xff00ff;
	textColor = glm::vec3(1.0f, 1.0f, 1.0f);
}

Button::~Button()
{
	delete shape;
	delete textElement;
}

void Button::Draw() {

	//draw shape
	shapeShader->use();
	shapeShader->setInt("color", buttonColor);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1));
	shapeShader->setMat4("model", model);
	shape->Draw();

	//draw text
	textShader->use();
	textShader->setVec3("textColor", textColor);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position - textElement->GetCenter(), 0.0f));
	textShader->setMat4("model", model);
	textElement->Draw();
}



void Button::Update() {
	CheckButton();
	ButtonUpdated();
}


void Button::CheckButton() {
	glm::vec2 mousePos = UIHandler::ScreenToUI(Input::GetMousePosition());

	glm::vec4 coords = ScreenMath::Get4OuterPoints(position, size);

	
	if (coords.x >= mousePos.x && coords.y <= mousePos.x && coords.z >= mousePos.y && coords.w <= mousePos.y) {
		if (!mouseInside) {
			mouseInside = true;
			MouseEntered();
			
		}
		MouseInside();

		Input::MouseIsOverUI();

		if (Input::GetMouseButtonPressed(0)) {
			ButtonPressed();
		}
		else if (Input::GetMouseButtonReleased(0)) {
			ButtonReleased();
		}
	}
	else if (mouseInside) {
		mouseInside = false;
		MouseExited();

		Input::MouseNotOverUI();
	}
	
}

void Button::ButtonPressed() {

}
void Button::ButtonReleased() {

}
void Button::MouseEntered() {

}
void Button::MouseInside() {

}
void Button::MouseExited() {

}

void Button::ButtonUpdated() {

}

void Button::SetText(std::string text) {
	textElement->SetText(text);
}
std::string Button::GetText() {
	return textElement->GetText();
}
