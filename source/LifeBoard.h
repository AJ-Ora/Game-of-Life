
#ifndef LIFEBOARD_H
#define LIFEBOARD_H

#pragma once

class LifeBoard 
{
public:
	LifeBoard();
	LifeBoard(bool* copyData, int width, int height);
	~LifeBoard();

	bool IsInitialized();

	bool GetPixelStatus(int x, int y);
	bool SetPixelStatus(int x, int y, bool isAlive);

	int GetWidth();
	int GetHeight();

	bool* storedData;

private:
	int width, height;
};

#endif
