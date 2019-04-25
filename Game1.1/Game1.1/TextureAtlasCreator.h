#pragma once


struct TextureAtlas {
	int width;
	int height;
	char*** image;

	~TextureAtlas() {
		if (image == nullptr) {
			return;
		}
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				delete[] image[i][j];
			}
			delete[] image[i];
		}
		delete[] image;
	}
};

//note this requres all the images to have the same size
//note this only works for one atlas at a time
namespace TextureAtlasCreator {
	void Init(int);
	void AddImageFile(const char*);
	void AddImageFiles(const char**, int);

	void CreateAtlas();

	TextureAtlas* GetAtlas();
	int GetWidth();
	int GetHeight();

	char* CompressTextureAtlas(int*);
	char* CompressTextureAtlas(TextureAtlas*, int*);

	void Uninit();
}

