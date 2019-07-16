#include "Button.h"
#include "UIHandler.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ScreenMath.h"


Button::Button() : UIElement()
{
	name = "Button";
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
	text = new TextElement(0.15f, "Hello, World!");

	size = glm::vec2(50, 20);

	//this code will lock the button to the corner of the screen
	//position = glm::vec2(UIHandler::GetUpperRight().x - (size.x / 2), UIHandler::GetUpperRight().y - (size.y / 2));
	position = ScreenMath::GetUpperRight(size);
	
	//textPosition = glm::vec2(size.x / 2, 0);
}


Button::~Button()
{
	delete shape;
	delete text;
}

void Button::Draw() {

	//draw shape
	shapeShader->use();
	shapeShader->setInt("color", 0xff00ff);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1));
	shapeShader->setMat4("model", model);
	shape->Draw();

	//draw text
	textShader->use();
	textShader->setVec3("textColor", glm::vec3(1.0f, 1.0f, 1.0f));

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position - text->GetCenter(), 0.0f));
	textShader->setMat4("model", model);
	text->Draw();
}
