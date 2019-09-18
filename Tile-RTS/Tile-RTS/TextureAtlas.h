#pragma once
#include <map>
#include <string>

//create largest positive number
#define SOLIDCOLOR (1 << 31) - 1

class TextureAtlas
{
public:
	TextureAtlas(int width, int height, int totalImages, int imagesInLength, int spacing, char*** image);
	TextureAtlas(TextureAtlas* ta);
	~TextureAtlas();

	void AddNewImageLocation(std::string name, int location);

	void SetImagePixel(int x, int y, int rgb, int value);

	char* Compress(int* size);

	int GetImageLocation(std::string name);
	int GetWidth();
	int GetHeight();
	int GetTotalImages();
	int GetTotalImagesInLength();
	int GetSpacing();
	char*** GetImage();

private:
	int width;
	int height;
	int totalImages;
	int imagesInLength;
	int spacing;
	char*** image;

	std::map<std::string, int> imageLocations;
};

