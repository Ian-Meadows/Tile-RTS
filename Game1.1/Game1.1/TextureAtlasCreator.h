#pragma once


struct TextureAtlas {
	int width;
	int height;
	char** image;
};

//note this requres all the images to have the same size
//note this only works for one atlas at a time
namespace TextureAtlasCreator {
	void Init(int);
	void AddImageFile(const char*);
	void AddImageFiles(const char**, int);

	void CreateAtlas();

	TextureAtlas* GetAtlas();

	char* CompressTextureAtlas();
	char* CompressTextureAtlas(TextureAtlas*);

	void Uninit();
}

