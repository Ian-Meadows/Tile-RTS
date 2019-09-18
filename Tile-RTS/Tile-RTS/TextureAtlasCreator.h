#pragma once
#include "TextureAtlas.h"


struct ImageFile {
	const char* path;
	const char* name;
	ImageFile(const char* path, const char* name) {
		this->path = path;
		this->name = name;
	}
};

//note this requres all the images to have the same size
//note this only works for one atlas at a time
namespace TextureAtlasCreator {
	void Init(int, int);
	void AddImageFile(const char* imagePath, const char* imageName);
	void AddImageFiles(const char** imagePaths, const char** imageNames, int size);

	void CreateAtlas();

	TextureAtlas* GetAtlas(bool newCopy);

	void Uninit();
}

