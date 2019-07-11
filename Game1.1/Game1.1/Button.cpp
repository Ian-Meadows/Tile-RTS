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

	position = glm::vec2(0, 0);
}


Button::~Button()
{
	delete shape;
}

void Button::Draw() {


	shapeShader->use();
	shapeShader->setInt("color", 0xffffff);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(20, 20, 1));
	shapeShader->setMat4("model", model);
	shape->Draw();
}
