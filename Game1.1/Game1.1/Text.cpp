#include "Text.h"
#include <glm/gtc/matrix_transform.hpp>


Text::Text() : UIElement() {
	position = glm::vec2(0, 0);
	scale = TEXT_DEFAULT_SCALE;
	text = "New Text";

	Init();
}

Text::Text(glm::vec2 pos) : UIElement() {
	position = pos;
	scale = TEXT_DEFAULT_SCALE;
	text = "New Text";

	Init();
}
Text::Text(glm::vec2 pos, float scale) : UIElement() {
	position = pos;
	this->scale = scale;

	Init();
}
Text::Text(glm::vec2 pos, std::string text) : UIElement() {
	position = pos;
	this->text = text;
	scale = TEXT_DEFAULT_SCALE;

	Init();
}
Text::Text(glm::vec2 pos, float scale, std::string text) : UIElement() {
	position = pos;
	this->scale = scale;
	this->text = text;

	Init();
}

Text::~Text()
{
	delete textElement;
}

void Text::Init() {
	name = "Text";

	textShader = UIHandler::GetTextShader();

	textShader->use();
	textElement = new TextElement(scale, text);
}

void Text::Draw() {
	textShader->use();
	textShader->setVec3("textColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	textShader->setMat4("model", model);
	textElement->Draw();
}
