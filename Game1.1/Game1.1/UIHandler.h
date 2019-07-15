#pragma once
#include "Shader.h"


#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
	GLuint     textureID;  // ID handle of the glyph texture
	glm::ivec2 size;       // Size of glyph
	glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
	GLuint     advance;    // Offset to advance to next glyph
};


namespace UIHandler {
	void Init();
	void Draw();
	void Uninit();

	Shader* GetTextShader();
	Shader* GetShapeShader();

	Character GetCharacter(char c);

	glm::vec2 GetUpperLeft();
	glm::vec2 GetUpperRight();
	glm::vec2 GetLowerLeft();
	glm::vec2 GetLowerRight();
}

