
#include "LifeBoard.h"

#include <string>

//#define STBI_ONLY_BMP

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb/stb_image_write.h"

LifeBoard::LifeBoard()
{
	storedData = nullptr;
	width = 0;
	height = 0;
}

LifeBoard::LifeBoard(std::string pathToImage)
{
	storedData = nullptr;
	width = 0;
	height = 0;

	ImportImage(pathToImage);
}

LifeBoard::LifeBoard(bool* copyData, int width, int height)
{
	if (copyData == nullptr)
	{
		storedData = nullptr;
		this->width = 0;
		this->height = 0;
		return;
	}

	int size = width * height;
	storedData = new bool[size];

#if WIN32
	memcpy_s(storedData, size, copyData, size);
#else
	memcpy(storedData, copyData, size);
#endif

	this->width = width;
	this->height = height;
}

LifeBoard::~LifeBoard()
{
	if (storedData == nullptr)
	{
		return;
	}

	delete[] storedData;
}

bool LifeBoard::IsInitialized()
{
	if (storedData == nullptr)
	{
		return false;
	}
	return true;
}

void LifeBoard::ImportImage(std::string pathToImage)
{
	int bitsPerPixel;
	unsigned char* importedData = stbi_load(pathToImage.c_str(), &width, &height, &bitsPerPixel, 1);

	if (importedData == nullptr)
	{
		return;
	}

	storedData = new bool[width * height];

	for (int i = 0; i < width * height; ++i)
	{
		int color = (int)*(importedData + i);
		if (color < 255 / 2)
		{
			storedData[i] = true;
		}
		else
		{
			storedData[i] = false;
		}
	}

	stbi_image_free(importedData);
}

unsigned char* LifeBoard::ToRGB()
{
	unsigned char* exportData = new unsigned char[width * height * 3];

	for (int i = 0; i < width * height; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			*(exportData + (i * 3 + j)) = *(storedData + i) ? 0 : 255;
		}
	}

	return exportData;
}

bool LifeBoard::GetPixelStatus(int x, int y)
{
	if (!IsInitialized())
	{
		return false;
	}

	if (x < 0 || x >= width)
	{
		return false;
	}

	if (y < 0 || y >= height)
	{
		return false;
	}

	return (bool)*(storedData + (y * width + x));
}

bool LifeBoard::SetPixelStatus(int x, int y, bool isAlive)
{
	if (!IsInitialized())
	{
		return false;
	}

	if (x < 0 || x >= width)
	{
		return false;
	}

	if (y < 0 || y >= height)
	{
		return false;
	}

	*(storedData + (y * width + x)) = isAlive;
	return true;
}

int LifeBoard::GetWidth()
{
	return width;
}

int LifeBoard::GetHeight()
{
	return height;
}
