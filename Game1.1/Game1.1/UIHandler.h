#pragma once
#include "Shader.h"


#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};


namespace UIHandler {
	void Init();
	void Draw();
	void Uninit();

	Shader* GetTextShader();
	Shader* GetShapeShader();

	glm::vec2 GetUpperLeft();
	glm::vec2 GetUpperRight();
	glm::vec2 GetLowerLeft();
	glm::vec2 GetLowerRight();
}

