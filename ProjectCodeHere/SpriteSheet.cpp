#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const char* imagePath, int numFrames)
	: Sprite (imagePath)
{
	this->frameWidth = getWidth();
	this->frameHeight = getHeight() / numFrames;
	this->numFrames = numFrames;
	this->firstFrame = 0;
}


SpriteSheet::~SpriteSheet()
{
}

bool SpriteSheet::validateSpritesheet() {
	if ((getWidth() * getHeight()) == (numFrames * (frameWidth * frameHeight)) && frameWidth == getWidth()) {
		return true;
	}
	else {
		return false;
	}
}

void SpriteSheet::fetchFrames() {
	// Loop over all elements of pixels  which is (width * height * 4) elements
	for (int pixelSet = 0; pixelSet < getWidth() * getHeight(); pixelSet++){
		int frameIndx = pixelSet / (frameWidth * frameHeight); // the index of frame that is being grabbed
		int framePos = pixelSet % (frameWidth * frameHeight); // position of set of pixels in the frame
		int pixelPos = pixelSet * 4; // position of set of pixels in the image

		// copy over the data from the pixels into each of the frames in the 32bit sets of 4 8bit unsigned chars
		frames[frameIndx][framePos + 0] = pixels[pixelPos + 0];
		frames[frameIndx][framePos + 1] = pixels[pixelPos + 1];
		frames[frameIndx][framePos + 2] = pixels[pixelPos + 2];
		frames[frameIndx][framePos + 3] = pixels[pixelPos + 3];
	}
}

void SpriteSheet::setFirstFrame(int firstFrame) {
	if (firstFrame >= 0 && firstFrame < numFrames) {
		this->firstFrame = firstFrame;
	}
	else {
		this->firstFrame = 0;
	}
}

stbi_uc* SpriteSheet::getFrame(int frameNum) {
	if (frameNum >= 0 && frameNum < numFrames) {
		return frames[frameNum];
	}
	else {
		return nullptr;
	}
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