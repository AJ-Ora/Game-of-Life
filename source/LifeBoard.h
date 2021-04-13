
#ifndef LIFEBOARD_H
#define LIFEBOARD_H

#pragma once

class LifeBoard 
{
public:
	LifeBoard();
	~LifeBoard();

	bool IsInitialized();

	bool IsPixelAlive(int x, int y);

private:
	int width, height, bitsPerPixel;
	unsigned char* rawData;
};

#endif
