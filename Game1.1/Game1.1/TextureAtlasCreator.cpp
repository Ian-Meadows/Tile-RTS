#include "TextureAtlasCreator.h"
#include <vector>
#include <math.h>



namespace TextureAtlasCreator {
	namespace {
		std::vector<const char*> files;
		int imageSizes;
		TextureAtlas* textureAtlas;
	}

	void TextureAtlasCreator::Init(int imageSizes) {
		TextureAtlasCreator::imageSizes = imageSizes;
		textureAtlas = nullptr;
	}

	void TextureAtlasCreator::AddImageFile(const char* file) {
		files.push_back(file);
	}
	void TextureAtlasCreator::AddImageFiles(const char** files, int size) {
		for (int i = 0; i < size; i++) {
			AddImageFile(files[i]);
		}
	}


	void TextureAtlasCreator::CreateAtlas() {
		if (textureAtlas != nullptr) {
			delete textureAtlas;
		}
		textureAtlas = new TextureAtlas();

		int total = files.size();
		
		int square = ceil(sqrt(total));
		int totalWidth = square * imageSizes;
		int totalHeight = totalWidth;

		for (int i = 0; i < total; i++) {

		}
	}

	TextureAtlas* TextureAtlasCreator::GetAtlas() {
		return textureAtlas;
	}

	char* TextureAtlasCreator::CompressTextureAtlas() {
		return nullptr;
	}
	char* CompressTextureAtlas(TextureAtlas* atlas) {
		return nullptr;
	}

	void Uninit() {
		if (textureAtlas != nullptr) {
			delete textureAtlas;
		}
	}
}
