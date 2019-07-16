#pragma once
#include "UIElement.h"
#include "UIHandler.h"
#include "TextElement.h"



class Text :
	public UIElement
{
public:
	Text();
	Text(glm::vec2 pos);
	Text(glm::vec2 pos, float scale);
	Text(glm::vec2 pos, std::string text);
	Text(glm::vec2 pos, float scale, std::string text);
	
	~Text();

	//note: shader must be already in use
	void Draw();

	void SetText(std::string text);
	std::string GetText();

	float scale;

private:

	TextElement* textElement;

	Shader* textShader;

	void Init(std::string text);
};

