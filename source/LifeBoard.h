
#ifndef LIFEBOARD_H
#define LIFEBOARD_H

#pragma once

/*
* Implements a way to store a 2-dimensional black-and-white board.
*
* Stores data as an array of booleans, which is not ideal because of how booleans work.
* One boolean is stored in one byte, which is the same size as a char.
* Due to time restrictions, a better storage solution couldn't be implemented.
*/

#include <string>

class LifeBoard 
{
public:
	LifeBoard();
	LifeBoard(std::string pathToImage);
	LifeBoard(bool* copyData, int width, int height);
	~LifeBoard();

	bool IsInitialized();

	void ImportImage(std::string pathToImage);
	unsigned char* ToRGB();

	bool GetPixelStatus(int x, int y);
	bool SetPixelStatus(int x, int y, bool isAlive);

	int GetWidth();
	int GetHeight();

	bool* storedData;

private:
	int width, height;
};

#endif
