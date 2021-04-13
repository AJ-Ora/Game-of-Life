
#include "LifeBoard.h"

#include <iostream>

#define STBI_ONLY_BMP

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb/stb_image_write.h"

LifeBoard::LifeBoard()
{
	rawData = stbi_load("image.bmp", &width, &height, &bitsPerPixel, 1);

	if (rawData == nullptr)
	{
		std::cout << "Failed to load image!" << std::endl;
		return;
	}
}

LifeBoard::~LifeBoard()
{
	if (rawData == nullptr)
	{
		return;
	}

	stbi_image_free(rawData);
}

bool LifeBoard::IsInitialized()
{
	if (rawData == nullptr)
	{
		return false;
	}
	return true;
}

bool LifeBoard::IsPixelAlive(int x, int y)
{
	if (x < 0 || x > width)
	{
		return false;
	}

	if (y < 0 || y > height) 
	{
		return false;
	}

	int color = (int)*(rawData + (y * width + x) * bitsPerPixel);
	std::cout << "Pixel color: " << color << std::endl;
	if (color > 255 / 2)
	{
		return false;
	}

	return true;
}
