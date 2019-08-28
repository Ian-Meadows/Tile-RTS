#pragma once
#include <string>
#include <glm/glm.hpp>
//create and store 255 different tile background images and colors

#define MAX_BG_TEXTURES 255


struct TileBackground {
	std::string name;

	//x:image number from texture atlas
	//y:color
	glm::ivec2 info;

	TileBackground(std::string name, glm::ivec2 info) {
		this->name = name;
		this->info = info;
	}
};

//call init before adding texures
namespace TileBackgroundHandler {
	//call before adding texures
	void Init();

	void Uninit();

	void AddTileBackground(std::string name, glm::ivec2 info);

	glm::ivec2 GetBackgroundInfo(std::string name);
}

