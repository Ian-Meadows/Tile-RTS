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
		int spacing;
		TextureAtlas* textureAtlas;
	}

	void TextureAtlasCreator::Init(int imageSizes, int spacing) {
		TextureAtlasCreator::imageSizes = imageSizes;
		TextureAtlasCreator::spacing = spacing;
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
		

		int total = files.size();
		int size = (int)ceil(sqrt((double)total));
		
		int totalWidth = size * imageSizes + (size * spacing);
		int totalHeight = size * imageSizes + (size * spacing);

		//init image in texture atlas
		char*** image = new char**[totalWidth];
		for (int i = 0; i < totalWidth; i++) {
			image[i] = new char*[totalHeight];
			for (int j = 0; j < totalHeight; j++) {
				image[i][j] = new char[4];
			}
		}

		//init to 0
		for (int x = 0; x < totalWidth; x++) {
			for (int y = 0; y < totalHeight; y++) {
				for (int z = 0; z < 4; z++) {
					image[x][y][z] = 0;
				}
			}
		}

		

		textureAtlas = new TextureAtlas(totalWidth, totalHeight, size*size, size, spacing, image);

		int width, height, nrChannels;

		//for width for loop
		int currentMaxWidth = imageSizes;
		int currentMaxHeight = imageSizes;
		int currentYStart = 0;
		int x = 0;
		int y = 0;

		for (int i = 0; i < total; i++) {
			unsigned char *data = stbi_load(files[i], &width, &height, &nrChannels, 0);
			if (data == nullptr) {
				std::cout << "failed to load image " << files[i] << ". Cannot create texture atlas. returning."<<std::endl;
				return;
			}
			std::cout << size << std::endl;
			int imageIndex = 0;

			//if image overflows and will be cut off
			if (x + width >= totalWidth) {
				currentMaxWidth = imageSizes;
				x = 0;
				currentMaxHeight += imageSizes + spacing;
				currentYStart += imageSizes + spacing;
				
			}
			
			for (; x < currentMaxWidth && x < totalWidth; x++) {
				for (y = currentYStart; y < currentMaxHeight && y < totalHeight; y++) {
					
					if (nrChannels == 4) {
						for (int z = 0; z < 4; z++) {
							textureAtlas->SetImagePixel(x, y, z, data[imageIndex]);
							imageIndex++;
						}
					}
					else if(nrChannels == 3){
						for (int z = 0; z < 3; z++) {
							textureAtlas->SetImagePixel(x, y, z, data[imageIndex]);
							imageIndex++;
						}
						textureAtlas->SetImagePixel(x, y, 3, 0xff);
						//imageIndex++;
					}
					else {
						std::cout << "what texture have you brought to this program? cannot make texture atlas. returning" << std::endl;
						return;
					}
				}
			}
			x += spacing;
			if (currentMaxWidth >= totalWidth) {
				currentMaxWidth = -spacing;
				x = 0;
				currentMaxHeight+= imageSizes + spacing;
				currentYStart += imageSizes + spacing;
			}
			currentMaxWidth += imageSizes + spacing;

			stbi_image_free(data);
			//std::cout << width << std::endl;
		}
	}

	TextureAtlas* TextureAtlasCreator::GetAtlas(bool newCopy) {
		if (textureAtlas == nullptr) {
			return nullptr;
		}
		else {
			if (newCopy) {
				return new TextureAtlas(textureAtlas);
			}
			else {
				return textureAtlas;
			}
		}
		
		
	}

	void TextureAtlasCreator::Uninit() {
		if (textureAtlas != nullptr) {
			delete textureAtlas;
		}
	}
}
