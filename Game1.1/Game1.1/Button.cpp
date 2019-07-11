#include "Button.h"
#include "UIHandler.h"
#include <glm/gtc/matrix_transform.hpp>


Button::Button() : UIElement()
{
	name = "Button";
	shapeShader = UIHandler::GetShapeShader();
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

	

	size = glm::vec2(50, 20);

	//this code will lock the button to the corner of the screen
	position = glm::vec2(UIHandler::GetUpperRight().x - (size.x / 2), UIHandler::GetUpperRight().y - (size.y / 2));
}


Button::~Button()
{
	delete shape;
}

void Button::Draw() {


	shapeShader->use();
	shapeShader->setInt("color", 0xff00ff);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1));
	shapeShader->setMat4("model", model);
	shape->Draw();
}
