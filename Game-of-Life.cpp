// Game-of-Life.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <thread>
#include <chrono>

#include "source/LifeBoard.h"
#include "source/LifeBoardLogic.h"

void printDebugLoop(LifeBoard& board);

int main(int argc, char* argv[])
{
	LifeBoard board;

	if (argc == 2)
	{
		board.ImportImage(argv[1]);
	}

	if (!board.IsInitialized())
	{
		std::cout << "Board not initialized, returning..." << std::endl;
		return -1;
	}

	printDebugLoop(board);

	return 0;
}

void printDebugLoop(LifeBoard& board)
{
	LifeBoardLogic logic;
	bool noCellsAlive = false;

	while (!noCellsAlive)
	{
		system("cls");

		logic.Step(board);

		noCellsAlive = true;
		for (int y = 0; y < board.GetHeight(); ++y)
		{
			for (int x = 0; x < board.GetWidth(); ++x)
			{
				if (board.GetPixelStatus(x, y) == true)
				{
					noCellsAlive = false;
					std::cout << "o ";
				}
				else
				{
					std::cout << "  ";
				}
			}
			std::cout << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 10));
	}
}
