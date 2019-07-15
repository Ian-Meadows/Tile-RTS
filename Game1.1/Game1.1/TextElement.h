#pragma once
#include <string>

#define TEXT_DEFAULT_SCALE 0.5f

class TextElement
{
public:
	TextElement();
	TextElement(float scale);
	TextElement(std::string text);
	TextElement(float scale, std::string text);
	~TextElement();

	void Draw();

	std::string text;

	float scale;

private:
	unsigned int VAO, VBO;

	void Init();
};

