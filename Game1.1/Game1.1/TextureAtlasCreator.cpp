#include "TextureAtlasCreator.h"
#include <vector>
#include <math.h>
#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



namespace TextureAtlasCreator {
	namespace {
		std::vector<const char*> files;
		int imageSizes;
		TextureAtlas* textureAtlas;
	}

	void TextureAtlasCreator::Init(int imageSizes) {
		TextureAtlasCreator::imageSizes = imageSizes;
		if (textureAtlas != nullptr) {
			delete textureAtlas;
		}
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

		//init image in texture atlas
		textureAtlas->image = new char**[totalWidth];
		for (int i = 0; i < totalWidth; i++) {
			textureAtlas->image[i] = new char*[totalHeight];
			for (int j = 0; j < totalHeight; j++) {
				textureAtlas->image[i][j] = new char[4];
			}
		}

		//init to 0
		for (int x = 0; x < totalWidth; x++) {
			for (int y = 0; y < totalHeight; y++) {
				for (int z = 0; z < 4; z++) {
					textureAtlas->image[x][y][z] = 0;
				}
			}
		}

		textureAtlas->width = totalWidth;
		textureAtlas->height = totalHeight;

		int width, height, nrChannels;
		for (int i = 0; i < total; i++) {
			unsigned char *data = stbi_load(files[i], &width, &height, &nrChannels, 0);
			if (data == nullptr) {
				std::cout << "failed to load image " << files[i] << ". Cannot create texture atlas returning."<<std::endl;
				return;
			}
			std::cout << nrChannels << std::endl;
			int imageIndex = 0;
			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					for (int z = 0; z < 4; z++) {
						textureAtlas->image[x][y][z] = data[imageIndex];
						imageIndex++;
					}
				}
			}


			stbi_image_free(data);
			//std::cout << width << std::endl;
		}
	}

	TextureAtlas* TextureAtlasCreator::GetAtlas() {
		return textureAtlas;
	}

	char* TextureAtlasCreator::CompressTextureAtlas(int* size) {
		if (textureAtlas == nullptr) {
			*size = 0;
			return nullptr;
		}
		int s = textureAtlas->width * textureAtlas->height * 4;
		*size = s;

		char* image = new char[s];
		
		int i = 0;
		for (int x = 0; x < textureAtlas->width; x++) {
			for (int y = 0; y < textureAtlas->height; y++) {
				for (int z = 0; z < 4; z++) {
					image[i] = textureAtlas->image[x][y][z];
					i++;
				}
			}
		}
		
		return image;
	}
	char* TextureAtlasCreator::CompressTextureAtlas(TextureAtlas* atlas, int* size) {

		if (atlas == nullptr) {
			*size = 0;
			return nullptr;
		}
		int s = atlas->width * atlas->height * 4;
		*size = s;

		char* image = new char[s];

		int i = 0;
		for (int x = 0; x < atlas->width; x++) {
			for (int y = 0; y < atlas->height; y++) {
				for (int z = 0; z < 4; z++) {
					image[i] = atlas->image[x][y][z];
					i++;
				}
			}
		}

		return image;
	}

	int TextureAtlasCreator::GetWidth() {
		if (textureAtlas == nullptr) {
			return 0;
		}
		return textureAtlas->width;
	}
	int TextureAtlasCreator::GetHeight() {
		if (textureAtlas == nullptr) {
			return 0;
		}
		return textureAtlas->height;
	}

	void TextureAtlasCreator::Uninit() {
		if (textureAtlas != nullptr) {
			delete textureAtlas;
		}
	}
}
