#include "UIHandler.h"
#include "SceneHandler.h"
#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>
#include <map>


#define CHARACTERS_TO_LOAD 128
#define CHARACTERS_HEIGHT 50

namespace UIHandler {
	namespace {
		//TODO::Create UI shaders(needs to handle text)
		Shader* textShader;
		Shader* shapeShader;

		Scene* currentScene = nullptr;

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection;

		glm::ivec2 resolution;
		
		std::map<GLchar, Character> characters;

		FT_Library ft;

		void LoadCharacters(FT_Face face);

		void LoadFeeType() {
			if (FT_Init_FreeType(&ft)) {
				std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			}

			FT_Face face;
			if (FT_New_Face(ft, "Fonts/arial.ttf", 0, &face)) {
				std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
			}

			//set font size(maybe)
			FT_Set_Pixel_Sizes(face, 0, CHARACTERS_HEIGHT);


			LoadCharacters(face);
		}

		void LoadCharacters(FT_Face face) {
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

			for (GLubyte c = 0; c < CHARACTERS_TO_LOAD; ++c)
			{
				// Load character glyph 
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph: " << (char)c << std::endl;
					continue;
				}
				// Generate texture
				GLuint texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// Now store character for later use
				Character character = {
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					face->glyph->advance.x
				};
				characters.insert(std::pair<GLchar, Character>(c, character));
			}
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // reenable byte-alignment restriction(i think)
			FT_Done_Face(face);
			FT_Done_FreeType(ft);
		}
		
	}

	void Init() {
		//create shaders
		textShader = new Shader("TextVertexShader.vert", "TextFragmentShader.frag");
		shapeShader = new Shader("ShapeVertexShader.vert", "ShapeFragmentShader.frag");

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));

		//TODO: actually setup for dynamic resolutions
		resolution = glm::ivec2(XRESOLUTION, YRESOLUTION);

		projection = glm::ortho(-(resolution.x / UI_PERSPECTIVE_SCALE), resolution.x / UI_PERSPECTIVE_SCALE,
			-(resolution.y / UI_PERSPECTIVE_SCALE), resolution.y / UI_PERSPECTIVE_SCALE,
			0.1f, 10.0f);


		LoadFeeType();
	}
	void Draw() {
		if (currentScene == nullptr) {
			currentScene = SceneHandler::GetCurrentScene();
		}
		else if (!currentScene->isActive) {
			currentScene = SceneHandler::GetCurrentScene();
		}

		shapeShader->use();
		shapeShader->setMat4("view", view);
		shapeShader->setMat4("projection", projection);
		
		textShader->use();
		textShader->setMat4("view", view);
		textShader->setMat4("projection", projection);

		//get ui in current scene
		std::vector<UIElement*>* ui = currentScene->GetUIElements();
		for (unsigned int i = 0; i < (*ui).size(); ++i) {
			(*ui)[i]->Draw();
		}

	}
	void Uninit() {
		delete shapeShader;

		//delete text texures
		for (GLubyte c = 0; c < CHARACTERS_TO_LOAD; ++c) {
			glDeleteTextures(1, &characters[c].textureID);
		}

	}


	Shader* UIHandler::GetTextShader() {
		return textShader;
	}
	Shader* UIHandler::GetShapeShader() {
		return shapeShader;
	}

	Character GetCharacter(char c) {
		return characters[c];
	}

	glm::ivec2 GetResolution() {
		return resolution;
	}
}
