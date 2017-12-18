#include "Sprite.h"

//imagePath - location of image file
Sprite::Sprite(const char* imagePath)
{
	pixels = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
	//imageSize = width * height * 4; //ERROR

	if (!pixels) {
		throw std::runtime_error("failed to load texture image!");
	}
}

Sprite::~Sprite()
{
}

//returns width of sprite
int Sprite::getWidth()
{
	return width;
}

//returns height of sprite
int Sprite::getHeight()
{
	return height;
}

//returns number of channels in the sprite
int Sprite::getChannels()
{
	return channels;
}

//returns array of pixels in the sprite
stbi_uc* Sprite::getPixels()
{
	return pixels;
}

/*
VkDeviceSize Sprite::getImageSize()
{
	return imageSize;							\\ERROR
}
*/

//changes the image the sprite has
void Sprite::changeSprite(const char* imagePath)
{
	if (path == imagePath) return;

	pixels = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
	//imageSize = width * height * 4; //ERROR

	if (!pixels) {
		throw std::runtime_error("failed to load texture image!");
	}
}