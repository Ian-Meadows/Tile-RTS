#pragma once
class TextureAtlas
{
public:
	TextureAtlas(int width, int height, int totalImages, int imagesInLength, int spacing, char*** image);
	TextureAtlas(TextureAtlas* ta);
	~TextureAtlas();


	void SetImagePixel(int x, int y, int rgb, int value);

	char* Compress(int* size);

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
};

