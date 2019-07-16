#include "Text.h"
#include <glm/gtc/matrix_transform.hpp>


Text::Text() : UIElement() {
	position = glm::vec2(0, 0);
	scale = TEXT_DEFAULT_SCALE;

	Init("New Text");
}

Text::Text(glm::vec2 pos) : UIElement() {
	position = pos;
	scale = TEXT_DEFAULT_SCALE;

	Init("New Text");
}
Text::Text(glm::vec2 pos, float scale) : UIElement() {
	position = pos;
	this->scale = scale;

	Init("New Text");
}
Text::Text(glm::vec2 pos, std::string text) : UIElement() {
	position = pos;
	scale = TEXT_DEFAULT_SCALE;

	Init(text);
}
Text::Text(glm::vec2 pos, float scale, std::string text) : UIElement() {
	position = pos;
	this->scale = scale;

	Init(text);
}

Text::~Text()
{
	delete textElement;
}

void Text::Init(std::string text) {
	name = "Text";

	textShader = UIHandler::GetTextShader();

	textShader->use();
	textElement = new TextElement(scale, text);
}

void Text::Draw() {
	textShader->use();
	textShader->setVec3("textColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position - textElement->GetCenter(), 0.0f));
	textShader->setMat4("model", model);
	textElement->Draw();
}

void Text::SetText(std::string text) {
	textElement->SetText(text);
}

std::string Text::GetText() {
	return textElement->GetText();
}
