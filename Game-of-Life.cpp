// Game-of-Life.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "source/LifeBoard.h"

int main()
{
	std::cout << "Hello CMake." << std::endl;

	LifeBoard board;

	if (!board.IsInitialized())
	{
		return -1;
	}

	bool alive = board.IsPixelAlive(0, 0);

	std::cout << "Pixel is " << (alive ? "alive" : "dead") << "!" << std::endl;

	return 0;
}
