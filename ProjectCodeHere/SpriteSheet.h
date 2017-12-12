#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Sprite.h"

class SpriteSheet : public Sprite
{
private:
	stbi_uc* pixels; // array of bytes representing the rgba values of pixels in the image
	unsigned int frameWidth;
	unsigned int frameHeight;
	unsigned int numFrames;
	unsigned int firstFrame;

	stbi_uc** frames = new stbi_uc*[numFrames]; // dynamic array of an array of pixels for each frames

public:
	SpriteSheet(const char* imagePath, int widthPx, int heightPx, int frameWidthPx, int frameHeightPx, int numFrames);
	~SpriteSheet();

	bool validateSpritesheet();
	void fetchFrames();

	void setFirstFrame(int firstFrame);

	int getFrameWidth();
	int getFrameHeight();
	int getNumFrames();
};

