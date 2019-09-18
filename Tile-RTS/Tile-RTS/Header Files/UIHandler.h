#pragma once
#include "Shader.h"


#include <ft2build.h>
#include FT_FREETYPE_H

#define UI_PERSPECTIVE_SCALE 5.0f

struct Character {
	GLuint     textureID;  // ID handle of the glyph texture
	glm::ivec2 size;       // Size of glyph
	glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
	GLuint     advance;    // Offset to advance to next glyph
};


namespace UIHandler {
	void Init();
	void Draw();
	void Update();
	void Uninit();

	Shader* GetTextShader();
	Shader* GetShapeShader();

	Character GetCharacter(char c);

	glm::ivec2 GetResolution();

	glm::vec2 ScreenToUI(glm::vec2 pos);

	glm::mat4 GetProjection();
	glm::mat4 GetView();
}

