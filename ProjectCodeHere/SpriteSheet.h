#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Sprite.h"

class SpriteSheet : public Sprite
{
private:
	stbi_uc* pixels; // array of bytes representing the rgba values of pixels in the image
	stbi_uc** frames = new stbi_uc*[numFrames]; // dynamic array of an array of pixels for each frames

	unsigned int frameWidth;
	unsigned int frameHeight;
	unsigned int numFrames;
	unsigned int firstFrame;


public:
	SpriteSheet(const char* imagePath, int widthPx, int heightPx, int frameWidthPx, int frameHeightPx, int numFrames);
	~SpriteSheet();

	// Returns true if the spritesheet has a valid frameWidth and frameHeight and numFrames
	bool validateSpritesheet();
	// Fills the frames array with the stbi_uc pointers representing the pixels.
	void fetchFrames();

	// Confirms the the new firstFrame exists and assigns it to be the firstFrame. Sets firstFrame to 0 if invalid parameter passed.
	void setFirstFrame(int firstFrame);

	// returns the stbi_uc pointer to the frame in the frames array at the passed position. Returns nullptr if position is invalid
	stbi_uc* getFrame(int frameNum);
	int getFrameWidth();
	int getFrameHeight();
	int getNumFrames();
};

