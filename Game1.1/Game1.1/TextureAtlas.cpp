#include "TextureAtlas.h"
#include <iostream>



TextureAtlas::TextureAtlas(int width, int height, int totalImages, int imagesInLength, int spacing, char*** image)
{
	this->width = width;
	this->height = height;
	this->totalImages = totalImages;
	this->imagesInLength = imagesInLength;
	this->spacing = spacing;
	this->image = image;
}

TextureAtlas::TextureAtlas(TextureAtlas* ta) {
	//clone basic info
	width = ta->width;
	height = ta->height;
	totalImages = ta->totalImages;
	imagesInLength = ta->imagesInLength;
	spacing = ta->spacing;

	//clone image
	//init image
	image = new char**[width];
	for (int i = 0; i < width; i++) {
		image[i] = new char*[height];
		for (int j = 0; j < height; j++) {
			image[i][j] = new char[4];
		}
	}

	//copy over image
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			for (int rgba = 0; rgba < 4; rgba++) {
				image[x][y][rgba] = ta->image[x][y][rgba];
			}
		}
	}

}

TextureAtlas::~TextureAtlas()
{
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

char* TextureAtlas::Compress(int* size) {
	if (image == nullptr) {
		*size = 0;
		return nullptr;
	}

	int s = width * height * 4;
	*size = s;

	char* compressedImage = new char[s];

	int i = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			for (int rgba = 0; rgba < 4; rgba++) {
				compressedImage[i] = image[x][y][rgba];
				i++;
			}
		}
	}

	return compressedImage;
}

void TextureAtlas::AddNewImageLocation(std::string name, int location) {
	imageLocations[name] = location;
}
int TextureAtlas::GetImageLocation(std::string name) {
	if (name == "none") {
		//gpu vertex shader expects largest negative number when using a solid color
		return (1 << 31);
	}
	else {
		return imageLocations[name];
	}
	
}

void TextureAtlas::SetImagePixel(int x, int y, int rgba, int value) {
	image[x][y][rgba] = value;
}
int TextureAtlas::GetWidth() {
	return width;
}
int TextureAtlas::GetHeight() {
	return height;
}
int TextureAtlas::GetTotalImages() {
	return totalImages;
}
int TextureAtlas::GetTotalImagesInLength() {
	return imagesInLength;
}
int TextureAtlas::GetSpacing() {
	return spacing;
}
char*** TextureAtlas::GetImage() {
	return image;
}
