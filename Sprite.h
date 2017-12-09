#pragma once
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


class Sprite
{
	private:
		const char* path; 
		int width;			//width of sprite in pixels
		int height;			//height of sprite in pixels
		int channels;		//number of color channels the sprite has
		stbi_uc* pixels;	//array of pixels in the sprite

	public:
		Sprite(const char* imagePath);
		~Sprite();
		int getWidth();
		int getHeight();
		int getChannels();
		stbi_uc* getPixels();
		void changeSprite(const char* imagePath);
};