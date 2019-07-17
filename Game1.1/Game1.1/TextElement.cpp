#include "TextElement.h"



TextElement::TextElement() {
	scale = TEXT_DEFAULT_SCALE;
	text = "";

	Init();
}
TextElement::TextElement(float scale) {
	this->scale = scale;
	text = "";

	Init();
}
TextElement::TextElement(std::string text) {
	scale = TEXT_DEFAULT_SCALE;
	this->text = text;

	Init();
}
TextElement::TextElement(float scale, std::string text) {
	this->scale = scale;
	this->text = text;

	Init();
}


TextElement::~TextElement()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void TextElement::Init() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	UpdateCenter();
}

void TextElement::Draw() {
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	glm::vec2 tempPos = glm::vec2(0, 0);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{

		Character ch = UIHandler::GetCharacter(*c);

		GLfloat xpos = tempPos.x + ch.bearing.x * scale;
		GLfloat ypos = tempPos.y - (ch.size.y - ch.bearing.y) * scale;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		tempPos.x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextElement::UpdateCenter() {

	if (text == "") {
		center = glm::vec2(0, 0);
		return;
	}

	glm::vec2 temp = glm::vec2(0, 0);

	size.y = 0;

	int total = 0;
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		++total;
		Character ch = UIHandler::GetCharacter(*c);
		temp.x += (ch.advance >> 6) * scale;
		temp.y += ch.size.y * scale;
		if (ch.size.y * scale > size.y) {
			size.y = ch.size.y * scale;
		}
	}
	center.x = temp.x / 2.0f;
	center.y = (temp.y / total) / 2.0f;

	size.x = temp.x;
	
}

void TextElement::SetText(std::string text) {
	this->text = text;
	UpdateCenter();
}
std::string TextElement::GetText() {
	return text;
}

glm::vec2 TextElement::GetCenter() {
	return center;
}

glm::vec2 TextElement::GetSize() {
	return size;
}