#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const char* imagePath, int widthPx, int heightPx, int frameWidthPx, int frameHeightPx, int numFrames)
	: Sprite (imagePath)
{
	this->frameWidth = frameWidthPx;
	this->frameHeight = frameHeightPx;
	this->numFrames = numFrames;
}


SpriteSheet::~SpriteSheet()
{
}

bool SpriteSheet::validateSpritesheet() {
	if ((getWidth() * getHeight()) == (numFrames * (frameWidth * frameHeight))) {
		return true;
	}
	else {
		return false;
	}
}


// Fills the frame array with the pixels for the frames in a vertical spriteSheet
void SpriteSheet::fetchFrames() {

	// Loop over all elements of pixels  which is (width * height * 4) elements
	for (int pixelSet = 0; pixelSet < getWidth() * getHeight(); pixelSet++){
		int frameIndx = pixelSet / (frameWidth * frameHeight); // the frame that is being grabbed
		int framePos = pixelSet % (frameWidth * frameHeight);
		int pixelPos = pixelSet * 4;

		frames[frameIndx][framePos + 0] = pixels[pixelPos + 0];
		frames[frameIndx][framePos + 1] = pixels[pixelPos + 1];
		frames[frameIndx][framePos + 2] = pixels[pixelPos + 2];
		frames[frameIndx][framePos + 3] = pixels[pixelPos + 3];
	}

}

void SpriteSheet::setFirstFrame(int firstFrame) {
	this->firstFrame = firstFrame;
}

int SpriteSheet::getFrameWidth() {
	return frameWidth;
}

int SpriteSheet::getFrameHeight() {
	return frameHeight;
}

int SpriteSheet::getNumFrames() {
	return numFrames;
}