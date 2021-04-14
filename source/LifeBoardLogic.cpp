
#include "LifeBoardLogic.h"

LifeBoardLogic::LifeBoardLogic()
{
}

LifeBoardLogic::~LifeBoardLogic()
{
}

void LifeBoardLogic::Step(LifeBoard& board)
{
	LifeBoard copy(board.storedData, board.GetWidth(), board.GetHeight());

	for (int y = 0; y < board.GetWidth(); ++y)
	{
		for (int x = 0; x < board.GetHeight(); ++x)
		{
			// Check the amount of alive neighbors
			int aliveNeighbors = 0;
			for (int neighborY = -1; neighborY <= 1; ++neighborY)
			{
				for (int neighborX = -1; neighborX <= 1; ++neighborX)
				{
					if (neighborX == 0 && neighborY == 0)
					{
						continue;
					}

					// Read value from copy (previous state)
					if (copy.GetPixelStatus(x + neighborX, y + neighborY) == true)
					{
						aliveNeighbors++;
					}
				}
			}

			if (copy.GetPixelStatus(x, y) == true)
			{
				if (aliveNeighbors < 2)
				{
					// Died by underpopulation
					board.SetPixelStatus(x, y, false);
				}

				if (aliveNeighbors > 3)
				{
					// Died by overpopulation
					board.SetPixelStatus(x, y, false);
				}
			}
			else
			{
				if (aliveNeighbors == 3)
				{
					// Became alive by reproduction
					board.SetPixelStatus(x, y, true);
				}
			}
		}
	}
}
