#pragma once
#include "TextureAtlas.h"


//note this requres all the images to have the same size
//note this only works for one atlas at a time
namespace TextureAtlasCreator {
	void Init(int, int);
	void AddImageFile(const char*);
	void AddImageFiles(const char**, int);

	void CreateAtlas();

	TextureAtlas* GetAtlas(bool newCopy);

	void Uninit();
}

