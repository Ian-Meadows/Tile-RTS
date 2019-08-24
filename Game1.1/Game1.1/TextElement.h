#pragma once
#include <string>
#include "UIHandler.h"

#define TEXT_DEFAULT_SCALE 0.5f

class TextElement
{
public:
	TextElement();
	TextElement(float scale);
	TextElement(std::string text);
	TextElement(float scale, std::string text);
	~TextElement();

	//note: shader must be already in use
	void Draw();

	void SetText(std::string text);
	std::string GetText();

	//Get where the center of the text is
	glm::vec2 GetCenter();

	//get the overall size of the text
	glm::vec2 GetSize();

	float scale;

private:
	unsigned int VAO, VBO;

	std::string text;

	//Center of where the text is rendered
	glm::vec2 center;

	//Size of text
	glm::vec2 size;

	void Init();

	//size also gets updated
	void UpdateCenter();
};

