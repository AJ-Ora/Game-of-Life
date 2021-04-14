// Game-of-Life.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "source/LifeBoard.h"
#include "source/LifeBoardLogic.h"

int main()
{
	std::cout << "Hello CMake." << std::endl;

	LifeBoard board;
	LifeBoardLogic logic;

	logic.Step(board);

	return 0;
}
