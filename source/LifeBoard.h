
#ifndef LIFEBOARD_H
#define LIFEBOARD_H

#pragma once

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

	bool GetPixelStatus(int x, int y);
	bool SetPixelStatus(int x, int y, bool isAlive);

	int GetWidth();
	int GetHeight();

	bool* storedData;

private:
	int width, height;
};

#endif
